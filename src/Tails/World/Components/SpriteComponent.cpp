#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/World/Level.hpp>

namespace tails
{
    SVector2f CSpriteComponent::getCentre() const noexcept
    {
        return size / 2.f + transform.getPosition();
    }

    SFloatRect CSpriteComponent::getLocalBounds() const noexcept
    {
        return {{0.f}, size};
    }

    void CSpriteComponent::onTick(float deltaSeconds)
    {
    }

    void CSpriteComponent::onRender(CLevelRenderBatch& renderBatch) const
    {
        if (!visible)
            return;

        renderBatch.addItem(
            getLayer(),
            getWorldTransform(),
            colour,
            size,
            texture
        );

        // right and bottom (size) is offset by left and top (position) for us by SDL
        /*
        if (!texture)
            render::rect(transform, size, colour);
        else
            render::texture(
                texture,
                transform,
                useTextureSize ? SVector2f {} : size,
                colour
            );
        */

        CComponent::onRender(renderBatch);
    }
}
