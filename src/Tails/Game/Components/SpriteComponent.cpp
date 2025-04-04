#include <Tails/Game/Components/SpriteComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    void CSpriteComponent::setSize(const SVector2f size)
    {
        m_size = size;
    }

    SVector2f CSpriteComponent::getSize() const
    {
        return m_size;
    }

    SVector2f CSpriteComponent::getCentre() const noexcept
    {
        return getSize() / 2.f + transform.position;
    }

    void CSpriteComponent::setColour(const SColour colour)
    {
        m_colour = colour;
    }

    SColour CSpriteComponent::getColour() const
    {
        return m_colour;
    }

    void CSpriteComponent::setTexture(std::shared_ptr<CTexture> texture)
    {
        m_texture = std::move(texture);
    }

    std::shared_ptr<CTexture> CSpriteComponent::getTexture() const
    {
        return m_texture;
    }

    SFloatRect CSpriteComponent::getGlobalBounds() const noexcept
    {
        return {transform.position, transform.position + m_size};
    }

    void CSpriteComponent::onRender(IRenderer& renderer) const
    {
        CPrimitiveComponent::onRender(renderer);

        // right and bottom (size) is offset by left and top (position) for us by SDL
        renderer.render({transform.position, m_size}, m_colour);
    }
}
