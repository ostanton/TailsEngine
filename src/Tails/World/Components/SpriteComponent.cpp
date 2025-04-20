#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    SVector2f CSpriteComponent::getCentre() const noexcept
    {
        return size / 2.f + transform.position;
    }

    SFloatRect CSpriteComponent::getGlobalBounds() const noexcept
    {
        return {transform.position, transform.position + size};
    }

    void CSpriteComponent::onRender(CRenderer& renderer) const
    {
        CPrimitiveComponent::onRender(renderer);

        if (!visible)
            return;

        // right and bottom (size) is offset by left and top (position) for us by SDL
        if (!texture)
            renderer.render({transform.position, size}, colour);
        else
            renderer.render(
                texture,
                transform.position,
                useTextureSize ? SVector2f {} : size,
                colour
            );
    }
}
