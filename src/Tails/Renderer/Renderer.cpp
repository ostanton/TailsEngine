#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Window.hpp>
#include <Tails/Log.hpp>

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

namespace tails
{
    CRenderer::CRenderer(const SVector2u size)
        : m_window(nullptr)
        , m_surface(SDL_CreateSurface(
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            SDL_PIXELFORMAT_RGBA8888
        ))
    {
        m_renderer = SDL_CreateSoftwareRenderer(m_surface);
    }

    CRenderer::CRenderer(CWindow& window)
        : m_window(&window)
        , m_surface(nullptr)
    {
        m_renderer = SDL_CreateRenderer(window.getInternal(), nullptr);
        int w, h;
        SDL_GetRenderOutputSize(m_renderer, &w, &h);
    }

    CRenderer::~CRenderer()
    {
        SDL_DestroyRenderer(m_renderer);
        
        if (m_surface)
            SDL_DestroySurface(m_surface);
    }

    void CRenderer::setRenderResolution(const SVector2i resolution, const bool integerScale)
    {
        SDL_SetRenderLogicalPresentation(
            m_renderer,
            resolution.x,
            resolution.y,
            integerScale ? SDL_LOGICAL_PRESENTATION_INTEGER_SCALE : SDL_LOGICAL_PRESENTATION_LETTERBOX
        );
    }

    SVector2i CRenderer::getRenderResolution() const
    {
        SVector2i resolution;
        SDL_RendererLogicalPresentation presentation;
        SDL_GetRenderLogicalPresentation(m_renderer, &resolution.x, &resolution.y, &presentation);
        return resolution;
    }

    bool CRenderer::isIntegerScaled() const
    {
        SVector2i resolution;
        SDL_RendererLogicalPresentation presentation;
        SDL_GetRenderLogicalPresentation(m_renderer, &resolution.x, &resolution.y, &presentation);
        return presentation == SDL_LOGICAL_PRESENTATION_INTEGER_SCALE;
    }

    SVector2u CRenderer::getOutputSize() const
    {
        SVector2i size;
        SDL_GetRenderOutputSize(m_renderer, &size.x, &size.y);
        return SVector2u {size};
    }

    void CRenderer::render(
        const STransform2D& transform,
        const SVector2f size,
        const SColour colour
    ) const
    {
        /**
         * TODO - separate into two things:
         * 1. Have some array of render items which is appended to here,
         * 2. Have another pass going through those items actually rendering them all at once.
         *
         * Is that better than this? Going through that array is fast yeah, but we can just render
         * here since we're here already. What do we gain from separating them into two passes?
         */
        const SDL_FRect myRect {
            transform.position.x,
            transform.position.y,
            size.x * transform.scale2D.x,
            size.y * transform.scale2D.y
        };
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderFillRect(m_renderer, &myRect);
    }

    void CRenderer::render(
        const std::shared_ptr<CTexture>& texture,
        const STransform2D& transform,
        const SVector2f size,
        const SColour tint
    ) const
    {
        render(texture, {}, transform, size, tint);
    }

    void CRenderer::render(
        const std::shared_ptr<CTexture>& texture,
        const SIntRect textureRect,
        const STransform2D& transform,
        const SVector2f size,
        const SColour tint
    ) const
    {
        // TODO - TSharedRef wrapping shared_ptr

        /**
         * TODO - std::unordered_map<std::weak_ptr<CTexture>, SDL_Texture*> ??
         * Render thinks on the same layer with the same texture together. If the weak ptr has expired,
         * remove the map entry and destroy the SDL_Texture. I want a separation between CTexture and SDL_Texture!
         */
        
        if (!texture)
        {
            TAILS_LOG(Renderer, Warning, "Render texture is invalid");
            return;
        }

        const SVector2f resized {
            (size.isZero() ? static_cast<float>(texture->getSize().x) : size.x) * transform.scale2D.x,
            (size.isZero() ? static_cast<float>(texture->getSize().y) : size.y) * transform.scale2D.y
        };
        
        if (!texture->getInternal())
        {
            // only create texture if the tails::CTexture doesn't have a pointer to an SDL_Texture already
            if (!texture->setInternal(SDL_CreateTexture(
                    m_renderer,
                    SDL_PIXELFORMAT_RGBA32,
                    SDL_TEXTUREACCESS_STATIC,
                    static_cast<int>(resized.x),
                    static_cast<int>(resized.y)
                )))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to update texture for rendering, '%s'", SDL_GetError());
                return;
            }
        }
        
        auto const tex = texture->getInternal();
        
        if (!tex)
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to create texture for rendering, '%s'", SDL_GetError());
            return;
        }
        
        if (!SDL_SetRenderDrawColor(m_renderer, tint.r, tint.g, tint.b, tint.a))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '%s'", SDL_GetError());
            return;
        }
        
        SDL_FRect srcRect;
        if (textureRect.isZero())
        {
            srcRect = SDL_FRect {
                0.f,
                0.f,
                static_cast<float>(texture->getSize().x),
                static_cast<float>(texture->getSize().y)
            };
        }
        else
        {
            srcRect = SDL_FRect {
                static_cast<float>(textureRect.position.x),
                static_cast<float>(textureRect.position.y),
                static_cast<float>(textureRect.size.x),
                static_cast<float>(textureRect.size.y)
            };
        }
        
        const SDL_FRect destRect {
            transform.position.x,
            transform.position.y,
            resized.x,
            resized.y
        };
        // TODO - rendering the texture crashes the PSP!!!
#ifndef TAILS_OS_PSP
        if (!SDL_RenderTexture(m_renderer, tex, &srcRect, &destRect))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render texture, '%s'", SDL_GetError());
        }
#else // TAILS_OS_PSP
        // just render a coloured rect instead
        if (!SDL_RenderRect(m_renderer, &destRect))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render rect, '%s'", SDL_GetError());
        }
#endif // TAILS_OS_PSP
    }

    void CRenderer::render(const CString& string) const
    {
        
    }

    void CRenderer::renderDebugText(
        const SVector2f position,
        const CString& string,
        const SColour colour
    ) const
    {
        // TODO - crashes the PSP!!
#ifndef TAILS_OS_PSP
#ifdef TAILS_DEBUG
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderDebugText(m_renderer, position.x, position.y, string.getData());
#endif // TAILS_DEBUG
#endif // TAILS_OS_PSP
    }

    std::shared_ptr<CTexture> CRenderer::getOutputTexture() const noexcept
    {
        // create a texture asset from the SDL_Surface
        SDL_Surface* surface {
            m_surface == nullptr ?
                SDL_GetWindowSurface(m_window->getInternal()) :
                m_surface
        };

        if (!surface)
        {
            TAILS_LOG(Renderer, Error, "Failed to get output texture, target surface is invalid");
            return nullptr;
        }
        
        auto const texture = SDL_CreateTextureFromSurface(m_renderer, surface);
        
        // TODO - support non-file assets in the asset manager!
        
        auto result = std::make_shared<CTexture>(
            SVector2u {SVector2i {m_surface->w, m_surface->h}},
            4,
            static_cast<u8*>(m_surface->pixels)
        );
        // TODO - do we want to keep this? I like the idea of creating SDL_Textures the frame we need them,
        // and not having them around between frames, but it's costly doing that
        result->setInternal(texture);
        
        return result;
    }

    void CRenderer::clear(const SColour colour) const
    {
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderClear(m_renderer);
    }

    void CRenderer::present() const
    {
        SDL_RenderPresent(m_renderer);
    }
}
