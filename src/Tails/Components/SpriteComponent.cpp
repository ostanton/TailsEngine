#include <Tails/Components/SpriteComponent.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CSpriteComponent::CSpriteComponent()
    {
        setSize({16.f, 16.f});
    }

    void CSpriteComponent::setTexture(const sf::Texture* texture)
    {
        m_texture = texture;
        if (!texture) return;

        setTextureCoords({{0, 0}, {texture->getSize().x, texture->getSize().y}});
    }

    void CSpriteComponent::setTextureCoords(const sf::Rect<unsigned int>& coords)
    {
        m_vertices[0].texCoords = {
            static_cast<float>(coords.position.x),
            static_cast<float>(coords.position.y)
        };
        m_vertices[1].texCoords = {
            static_cast<float>(coords.position.x),
            static_cast<float>(coords.position.y) + static_cast<float>(coords.size.y)
        };
        m_vertices[2].texCoords = {
            static_cast<float>(coords.position.x) + static_cast<float>(coords.size.x),
            static_cast<float>(coords.position.y)
        };
        m_vertices[3].texCoords = {
            static_cast<float>(coords.position.x) + static_cast<float>(coords.size.x),
            static_cast<float>(coords.position.y) + static_cast<float>(coords.size.y)
        };
    }

    sf::Rect<unsigned int> CSpriteComponent::getTextureCoords() const
    {
        return sf::Rect<unsigned int>({
            {
                static_cast<unsigned int>(m_vertices[0].texCoords.x),
                static_cast<unsigned int>(m_vertices[0].texCoords.y)
            },
            {
                static_cast<unsigned int>(m_vertices[3].texCoords.x),
                static_cast<unsigned int>(m_vertices[3].texCoords.y)
            }
        });
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

    void CSpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        CComponent::draw(target, states);
        
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, states);
    }

    sf::FloatRect CSpriteComponent::getGlobalBounds() const
    {
        return getTransform().transformRect(m_vertices.getBounds());
    }
}
