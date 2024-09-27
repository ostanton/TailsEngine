#include <Tails/SpriteComponent.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CSpriteComponent::CSpriteComponent()
    {
        setSize({16.f, 16.f});
    }

    void CSpriteComponent::setTexture(sf::Texture* texture)
    {
        m_texture = texture;
        if (!texture) return;

        m_vertices[0].texCoords = {0.f, 0.f};
        m_vertices[1].texCoords = {0.f, static_cast<float>(texture->getSize().y)};
        m_vertices[2].texCoords = {static_cast<float>(texture->getSize().x), 0.f};
        m_vertices[3].texCoords = {
            static_cast<float>(texture->getSize().x),
            static_cast<float>(texture->getSize().y)
        };
    }

    void CSpriteComponent::setSize(const sf::Vector2f& size)
    {
        m_vertices[0].position = {0.f, 0.f};
        m_vertices[1].position = {0.f, size.y};
        m_vertices[2].position = {size.x, 0.f};
        m_vertices[3].position = {size.x, size.y};
    }

    const sf::Vector2f& CSpriteComponent::getSize() const
    {
        return m_vertices[3].position;
    }

    void CSpriteComponent::setColour(sf::Color colour)
    {
        for (size_t i {0}; i < m_vertices.getVertexCount(); i++)
        {
            m_vertices[i].color = colour;
        }
    }

    sf::Color CSpriteComponent::getColour() const
    {
        return m_vertices[0].color;
    }

    void CSpriteComponent::serialise(nlohmann::json& obj) const
    {
        
    }

    void CSpriteComponent::deserialise(const nlohmann::json& obj)
    {
        
    }

    void CSpriteComponent::tick(float deltaTime)
    {
        
    }

    void CSpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, states);
    }

    sf::FloatRect CSpriteComponent::getGlobalBounds() const
    {
        return getTransform().transformRect(m_vertices.getBounds());
    }
}
