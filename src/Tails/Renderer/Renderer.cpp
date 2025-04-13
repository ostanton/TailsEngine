#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Renderer/RenderItem.hpp>
#include <Tails/Assets/Texture.hpp>

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
        auto const tex = SDL_CreateTexture(
            m_renderer,
            SDL_PIXELFORMAT_RGB24, // TODO - make these actually make sense
            SDL_TEXTUREACCESS_STATIC,
            static_cast<int>(texture->getSize().x),
            static_cast<int>(texture->getSize().y)
        );
        
        if (!tex)
        {
            // TODO - fail!
        }
        
        if (!SDL_UpdateTexture(tex, nullptr, texture->getPixels(), static_cast<int>(texture->getSize().x)))
        {
            // TODO - fail!
        }
        
        SDL_SetRenderDrawColor(m_renderer, tint.r, tint.g, tint.b, tint.a);
        const SDL_FRect destRect {position.x, position.y, size.x, size.y};
        SDL_RenderTexture(m_renderer, tex, nullptr, &destRect);
        SDL_DestroyTexture(tex);
    }

    void IRenderer::render(const CString& string) const
    {
        
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
