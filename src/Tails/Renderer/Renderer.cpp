#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Log.hpp>

#include "../ApplicationImpl.hpp"

#include <SDL3/SDL_render.h>

namespace tails::render
{
    namespace
    {
        SDL_Renderer* gRendererPtr {nullptr};
    }

    void init()
    {
        // TODO - maybe want to have getting the window be a bit cleaner?? Have this cpp in Application.cpp??
        gRendererPtr = SDL_CreateRenderer(app::impl::getWindow(), nullptr);
    }

    void deinit()
    {
        SDL_DestroyRenderer(gRendererPtr);
    }

    void clear(const SColour colour)
    {
        SDL_SetRenderDrawColor(gRendererPtr, colour.r, colour.g, colour.b, colour.a);
        SDL_RenderClear(gRendererPtr);
    }

    void present()
    {
        SDL_RenderPresent(gRendererPtr);
    }

    SVector2u getResolution()
    {
        SVector2i resolution;
        SDL_RendererLogicalPresentation presentation;
        SDL_GetRenderLogicalPresentation(gRendererPtr, &resolution.x, &resolution.y, &presentation);
        return SVector2u {resolution};
    }

    void texture(
        const TSharedRef<CTexture>& texture,
        const STransform2D& transform,
        const SVector2f size,
        const SColour tint,
        const SIntRect textureRect
    )
    {
        const SVector2f resized {
            (size.isZero() ? static_cast<float>(texture->getSize().x) : size.y) * transform.scale2D.x,
            (size.isZero() ? static_cast<float>(texture->getSize().y) : size.y) * transform.scale2D.y
        };

        if (!texture->getInternal())
        {
            // only create texture if the tails::CTexture doesn't have a pointer to an SDL_Texture already
            if (!texture->setInternal(SDL_CreateTexture(
                    gRendererPtr,
                    SDL_PIXELFORMAT_RGBA32,
                    SDL_TEXTUREACCESS_STATIC,
                    static_cast<int>(resized.x),
                    static_cast<int>(resized.y)
                )))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to create texture for rendering, '{}'", SDL_GetError());
                return;
            }
        }

        auto const tex = texture->getInternal();

        if (!SDL_SetRenderDrawColor(gRendererPtr, tint.r, tint.g, tint.b, tint.a))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '{}'", SDL_GetError());
            return;
        }

        SDL_FRect srcRect;
        if (textureRect.isZero())
        {
            srcRect = {
                .x = 0.f,
                .y = 0.f,
                .w = static_cast<float>(texture->getSize().x),
                .h = static_cast<float>(texture->getSize().y)
            };
        }
        else
        {
            srcRect = {
                .x = static_cast<float>(textureRect.position.x),
                .y = static_cast<float>(textureRect.position.y),
                .w = static_cast<float>(textureRect.size.x),
                .h = static_cast<float>(textureRect.size.y)
            };
        }

        const SDL_FRect destRect = {
            .x = transform.position.x,
            .y = transform.position.y,
            .w = resized.x,
            .h = resized.y
        };

#ifndef TAILS_OS_PSP
        // TODO - crashes PSP
        if (!SDL_RenderTexture(gRendererPtr, tex, &srcRect, &destRect))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render texture, '{}'", SDL_GetError());
        }
#else // TAILS_OS_PSP
        if (!SDL_RenderRect(gRendererPtr, &destRect))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render rect, '{}'", SDL_GetError());
        }
#endif // TAILS_OS_PSP
    }

    void rect(
        const STransform2D& transform,
        const SVector2f size,
        const SColour fillColour,
        const SColour outlineColour
    )
    {
        const SVector2f resized {
            size.x * transform.scale2D.x,
            size.y * transform.scale2D.y
        };

        if (fillColour != SColour::transparent)
        {
            if (!SDL_SetRenderDrawColor(gRendererPtr, fillColour.r, fillColour.g, fillColour.b, fillColour.a))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '{}'", SDL_GetError());
            }
            const SDL_FRect rect {
                .x = transform.position.x,
                .y = transform.position.y,
                .w = resized.x,
                .h = resized.y
            };
            if (!SDL_RenderFillRect(gRendererPtr, &rect))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to render rect, '{}'", SDL_GetError());
            }
        }

        if (outlineColour != SColour::transparent)
        {
            if (!SDL_SetRenderDrawColor(gRendererPtr, outlineColour.r, outlineColour.g, outlineColour.b, outlineColour.a))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '{}'", SDL_GetError());
            }
            const SDL_FRect rect {
                .x = transform.position.x,
                .y = transform.position.y,
                .w = resized.x,
                .h = resized.y
            };
            if (!SDL_RenderFillRect(gRendererPtr, &rect))
            {
                TAILS_LOG_VA(Renderer, Error, "Failed to render rect, '{}'", SDL_GetError());
            }
        }
    }

    void debugText(
        const STransform2D& transform,
        const CString& string,
        const SColour colour,
        const std::shared_ptr<CFont>& font
    )
    {
#ifdef TAILS_DEBUG
        if (!SDL_SetRenderDrawColor(gRendererPtr, colour.r, colour.g, colour.b, colour.a))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to set renderer colour, '{}'", SDL_GetError());
            return;
        }
#ifndef TAILS_OS_PSP
        // TODO - crashes PSP
        if (!SDL_RenderDebugText(gRendererPtr, transform.position.x, transform.position.y, string.getData()))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render text '{}', '{}'", string.getData(), SDL_GetError());
        }
#endif // TAILS_OS_PSP
#endif // TAILS_DEBUG
    }
}
