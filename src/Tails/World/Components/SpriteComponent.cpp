#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    SVector2f CSpriteComponent::getCentre() const noexcept
    {
        return size / 2.f + transform.position;
    }

    void CSpriteComponent::onTick(float deltaSeconds)
    {
    }

    void CSpriteComponent::onRender() const
    {
        if (!visible)
            return;

        // right and bottom (size) is offset by left and top (position) for us by SDL
        if (!texture)
            render::rect(transform, size, colour);
        else
            render::texture(
                texture,
                transform,
                useTextureSize ? SVector2f {} : size,
                colour
            );

        CComponent::onRender();
    }
}
