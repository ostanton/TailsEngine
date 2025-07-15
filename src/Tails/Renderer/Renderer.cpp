#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Renderer/Vertex.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Log.hpp>
#include <Tails/Maths/FloatColour.hpp>
#include <Tails/Memory.hpp>

#include "../WindowImpl.hpp"

#include <SDL3/SDL_render.h>

#include <vector>

namespace tails::render
{
    namespace
    {
        SDL_Renderer* gRendererPtr {nullptr};
    }

    void init()
    {
        // TODO - maybe want to have getting the window be a bit cleaner?? Have this cpp in Application.cpp??
        auto const window = window::impl::getWindow();
        gRendererPtr = SDL_CreateRenderer(window, nullptr);
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

        SVertex vertices[4];

        const auto& matrix = screenTransform.getMatrix();
        for (u8 i {0}; i < 4; i++)
        {
            const SVector2f position {matrix.transform(points[i])};
            vertices[i].position = position;
            vertices[i].colour = fillColour;
            vertices[i].texCoord = 0.f;
        }

        const int indices[6] = {0, 1, 2, 2, 3, 0};
        geometry({vertices, 4}, {indices, 6});
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

    void debugLines(const std::span<const SVector2f> points, const SFloatColour colour)
    {
        if (points.size() < 2)
            return;

        std::vector<SDL_FPoint> sdlPoints;
        sdlPoints.reserve(points.size());
        for (usize i {0}; i < points.size(); i++)
        {
            const SVector2f point = points[i];
            sdlPoints.emplace_back(point.x, point.y);
        }

        SDL_SetRenderDrawColorFloat(
            gRendererPtr,
            colour.r,
            colour.g,
            colour.b,
            colour.a
        );
        SDL_RenderLines(gRendererPtr, sdlPoints.data(), static_cast<int>(points.size()));
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

    void geometry(
        const std::span<const SVertex> vertices,
        const std::span<const int> indices,
        const std::shared_ptr<CTexture>& texture
    )
    {
        // could have some reusable buffer here instead (I think vector uses SBO anyway though)
        std::vector<SDL_Vertex> sdlVertices {vertices.size()};
        for (usize i {0}; i < vertices.size(); i++)
        {
            const auto& [position, colour, texCoord] = vertices[i];
            sdlVertices[i].position = {
                .x = position.x,
                .y = position.y,
            };
            sdlVertices[i].color = {
                .r = colour.r,
                .g = colour.g,
                .b = colour.b,
                .a = colour.a,
            };
            sdlVertices[i].tex_coord = {
                .x = texCoord.x,
                .y = texCoord.y,
            };
        }

        if (!SDL_RenderGeometry(
                gRendererPtr,
                texture ? texture->getInternal() : nullptr,
                sdlVertices.data(),
                static_cast<int>(vertices.size()),
                indices.data(),
                static_cast<int>(indices.size())
            ))
        {
            TAILS_LOG(Renderer, Error, TAILS_FMT("Failed to render geometry, '{}'", SDL_GetError()));
        }
    }
}
