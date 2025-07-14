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
        //SDL_SetRenderLogicalPresentation(gRendererPtr, 1280, 720, SDL_LOGICAL_PRESENTATION_LETTERBOX);
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

    SVector2f getResolution()
    {
        SDL_FRect res;
        SDL_GetRenderLogicalPresentationRect(gRendererPtr, &res);
        return {res.w, res.h};
    }

    void texture(
        const TSharedRef<CTexture>& texture,
        const STransform2D& screenTransform,
        const SVector2f size,
        const SColour tint,
        const SIntRect textureRect
    )
    {
        // TODO - full transform via geometry like rect()
        const SVector2f resized {
            (size.isZero() ? static_cast<float>(texture->getSize().x) : size.y) * screenTransform.getScale().x,
            (size.isZero() ? static_cast<float>(texture->getSize().y) : size.y) * screenTransform.getScale().y
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
            .x = screenTransform.getPosition().x,
            .y = screenTransform.getPosition().y,
            .w = resized.x,
            .h = resized.y
        };

#ifndef TAILS_OS_PSP
        // TODO - crashes PSP
        if (!SDL_RenderTextureRotated(gRendererPtr, tex, &srcRect, &destRect, screenTransform.getRotation().asDegrees(), nullptr, SDL_FLIP_NONE))
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
        const STransform2D& screenTransform,
        const SVector2f size,
        const SColour fillColour,
        const SColour outlineColour // TODO - do we need outline colour?
    )
    {
        // TODO - origin doesn't seem to work
        const SVector2f originOffset {
            screenTransform.getOrigin().x * size.x,
            screenTransform.getOrigin().y * size.y
        };
        const SVector2f points[4] = {
            SVector2f {0.f, 0.f} - originOffset,
            SVector2f {size.x, 0.f} - originOffset,
            size - originOffset,
            SVector2f {0.f, size.y} - originOffset,
        };

        SDL_Vertex vertices[4];

        const auto& matrix = screenTransform.getMatrix();
        for (u8 i {0}; i < 4; i++)
        {
            const SVector2f position {matrix.transform(points[i])};
            vertices[i].position.x = position.x;
            vertices[i].position.y = position.y;
            // TODO - some SFloatColour struct
            vertices[i].color = {
                .r = static_cast<float>(fillColour.r) / 255,
                .g = static_cast<float>(fillColour.g) / 255,
                .b = static_cast<float>(fillColour.b) / 255,
                .a = static_cast<float>(fillColour.a) / 255
            };
            vertices[i].tex_coord = {.x = 0.f, .y = 0.f};
        }

        const int indices[6] = {0, 1, 2, 2, 3, 0};
        if (!SDL_RenderGeometry(gRendererPtr, nullptr, vertices, 4, indices, 6))
        {
            TAILS_LOG(Renderer, Error, TAILS_FMT("Failed to render rect, '{}'", SDL_GetError()));
        }
    }

    void debugText(
        const STransform2D& screenTransform,
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
        if (!SDL_RenderDebugText(gRendererPtr, screenTransform.getPosition().x, screenTransform.getPosition().y, string.getData()))
        {
            TAILS_LOG_VA(Renderer, Error, "Failed to render text '{}', '{}'", string.getData(), SDL_GetError());
        }
#endif // TAILS_OS_PSP
#endif // TAILS_DEBUG
    }

    void quad(const STransform2D& screenTransform, const SVector2f size, const SColour colour)
    {
        const SDL_FColor sdlColour {
            .r = static_cast<float>(colour.r),
            .g = static_cast<float>(colour.g),
            .b = static_cast<float>(colour.b),
            .a = static_cast<float>(colour.a),
        };
        const SDL_Vertex vertices[] = {
            SDL_Vertex {
                .position = SDL_FPoint {
                    .x = screenTransform.getPosition().x,
                    .y = screenTransform.getPosition().y
                },
                .color = sdlColour,
                .tex_coord = {0.f, 0.f},
            },
            SDL_Vertex {
                .position = SDL_FPoint {
                    .x = screenTransform.getPosition().x,
                    .y = screenTransform.getPosition().y + size.y
                },
                .color = sdlColour,
                .tex_coord = {1.f, 0.f},
            },
            SDL_Vertex {
                .position = SDL_FPoint {
                    .x = screenTransform.getPosition().x + size.x,
                    .y = screenTransform.getPosition().y
                },
                .color = sdlColour,
                .tex_coord = {1.f, 1.f},
            },
            SDL_Vertex {
                .position = SDL_FPoint {
                    .x = screenTransform.getPosition().x + size.x,
                    .y = screenTransform.getPosition().y + size.y
                },
                .color = sdlColour,
                .tex_coord = {0.f, 1.f},
            },
        };
        const int indices[] = {
            0, 1, 2,
            2, 3, 0
        };
        SDL_RenderGeometry(
            gRendererPtr,
            nullptr,
            vertices,
            4,
            indices,
            6
        );
    }
}
