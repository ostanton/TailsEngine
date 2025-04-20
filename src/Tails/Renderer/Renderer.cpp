#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Renderer/RenderItem.hpp>
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

    void CRenderer::render(const IRenderItem& item)
    {
        item.onRender(*this);
    }

    void CRenderer::render(const SFloatRect& rect, const SColour colour) const
    {
        /**
         * TODO - separate into two things:
         * 1. Have some array of render items which is appended to here,
         * 2. Have another pass going through those items actually rendering them all at once.
         *
         * Is that better than this? Going through that array is fast yeah, but we can just render
         * here since we're here already. What do we gain from separating them into two passes?
         */
        const SDL_FRect myRect {rect.position.x, rect.position.y, rect.size.x, rect.size.y};
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderFillRect(m_renderer, &myRect);
    }

    void CRenderer::render(
        const std::shared_ptr<CTexture>& texture,
        const SVector2f position,
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
        
        if (!texture->getInternal())
        {
            // only create texture if the tails::CTexture doesn't have a pointer to an SDL_Texture already
            if (!texture->setInternal(SDL_CreateTexture(
                    m_renderer,
                    SDL_PIXELFORMAT_RGBA32,
                    SDL_TEXTUREACCESS_STATIC,
                    size.isZero() ? static_cast<int>(texture->getSize().x) : static_cast<int>(size.x),
                    size.isZero() ? static_cast<int>(texture->getSize().y) : static_cast<int>(size.y)
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
        
        const SDL_FRect destRect {position.x, position.y, size.x, size.y};
        // TODO - rendering the texture crashes the PSP!!!
#ifndef TAILS_OS_PSP
        if (!SDL_RenderTexture(m_renderer, tex, nullptr, &destRect))
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
