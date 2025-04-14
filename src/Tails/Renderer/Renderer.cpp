#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Log.hpp>

#include <SDL3/SDL_render.h>

namespace tails
{
    IRenderer::~IRenderer()
    {
        SDL_DestroyRenderer(m_renderer);
    }

    void IRenderer::setRenderResolution(const SVector2i resolution, const bool integerScale)
    {
        SDL_SetRenderLogicalPresentation(
            m_renderer,
            resolution.x,
            resolution.y,
            integerScale ? SDL_LOGICAL_PRESENTATION_INTEGER_SCALE : SDL_LOGICAL_PRESENTATION_LETTERBOX
        );
    }

    SVector2i IRenderer::getRenderResolution() const
    {
        SVector2i resolution;
        SDL_RendererLogicalPresentation presentation;
        SDL_GetRenderLogicalPresentation(m_renderer, &resolution.x, &resolution.y, &presentation);
        return resolution;
    }

    bool IRenderer::isIntegerScaled() const
    {
        SVector2i resolution;
        SDL_RendererLogicalPresentation presentation;
        SDL_GetRenderLogicalPresentation(m_renderer, &resolution.x, &resolution.y, &presentation);
        return presentation == SDL_LOGICAL_PRESENTATION_INTEGER_SCALE;
    }

    SVector2i IRenderer::getOutputSize() const
    {
        SVector2i size;
        SDL_GetRenderOutputSize(m_renderer, &size.x, &size.y);
        return size;
    }

    SDL_Window* IRenderer::getRenderWindow() const
    {
        return SDL_GetRenderWindow(m_renderer);
    }

    void IRenderer::render(const IRenderItem& item)
    {
        item.onRender(*this);
    }

    void IRenderer::render(const SFloatRect& rect, const SColour colour) const
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

    void IRenderer::render(
        const std::shared_ptr<CTexture>& texture,
        const SVector2f position,
        const SVector2f size,
        const SColour tint
    ) const
    {
        // TODO - TSharedRef wrapping shared_ptr
        if (!texture)
        {
            TAILS_LOG(Renderer, Warning, "Render texture is invalid");
            return;
        }

        auto const tex = SDL_CreateTexture(
            m_renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STATIC,
            size.isZero() ? static_cast<int>(texture->getSize().x) : static_cast<int>(size.x),
            size.isZero() ? static_cast<int>(texture->getSize().y) : static_cast<int>(size.y)
        );
        
        if (!tex)
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to create texture for rendering, '%s'", SDL_GetError());
            SDL_DestroyTexture(tex);
            return;
        }
        
        if (!SDL_UpdateTexture(tex, nullptr, texture->getPixels(), static_cast<int>(texture->getPitch())))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to update texture for rendering, '%s'", SDL_GetError());
            SDL_DestroyTexture(tex);
            return;
        }
        
        if (!SDL_SetRenderDrawColor(m_renderer, tint.r, tint.g, tint.b, tint.a))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '%s'", SDL_GetError());
            SDL_DestroyTexture(tex);
            return;
        }
        
        const SDL_FRect destRect {position.x, position.y, size.x, size.y};
        // TODO - rendering the texture crashes the PSP!!!
#ifndef TAILS_OS_PSP
        if (!SDL_RenderTexture(m_renderer, tex, nullptr, &destRect))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render texture, '%s'", SDL_GetError());
        }
#endif // TAILS_OS_PSP
        
        SDL_DestroyTexture(tex);
    }

    void IRenderer::render(const CString& string) const
    {
        
    }

    void IRenderer::renderDebugText(
        const SVector2f position,
        const CString& string,
        const SColour colour
    ) const
    {
#ifdef TAILS_DEBUG
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderDebugText(m_renderer, position.x, position.y, string.getData());
#endif // TAILS_DEBUG
    }

    void IRenderer::clear(const SColour colour) const
    {
        SDL_SetRenderDrawColor(m_renderer, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderClear(m_renderer);
    }

    void IRenderer::present() const
    {
        SDL_RenderPresent(m_renderer);
    }
}
