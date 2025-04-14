#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Assets/Texture.hpp>

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

    SColour CSpriteComponent::getColour() const noexcept
    {
        return m_colour;
    }

    void CSpriteComponent::setTexture(std::shared_ptr<CTexture> texture)
    {
        m_texture = std::move(texture);
    }

    std::shared_ptr<CTexture> CSpriteComponent::getTexture() const noexcept
    {
        return m_texture;
    }

    void CSpriteComponent::setUseTextureSize(const bool useTextureSize)
    {
        m_useTextureSize = useTextureSize;
    }

    bool CSpriteComponent::getUseTextureSize() const noexcept
    {
        return m_useTextureSize;
    }

    SFloatRect CSpriteComponent::getGlobalBounds() const noexcept
    {
        return {transform.position, transform.position + m_size};
    }

    void CSpriteComponent::onRender(IRenderer& renderer) const
    {
        CPrimitiveComponent::onRender(renderer);

        // right and bottom (size) is offset by left and top (position) for us by SDL
        if (!m_texture)
            renderer.render({transform.position, m_size}, m_colour);
        else
            renderer.render(
                m_texture,
                transform.position,
                m_useTextureSize ? SVector2f {m_texture->getSize()} : m_size,
                m_colour
            );
    }
}
