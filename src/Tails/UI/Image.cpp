#include <Tails/UI/Image.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tails::ui
{
    void CImage::setTexture(const sf::Texture* texture)
    {
        m_texture = texture;
        updateTexCoords();
    }

    const sf::Texture* CImage::getTexture() const
    {
        return m_texture;
    }

    void CImage::setSize(const sf::Vector2f size)
    {
        m_vertices[1].position = {0.f, size.y};
        m_vertices[2].position = {size.x, 0.f};
        m_vertices[3].position = size;
    }

    sf::Vector2f CImage::getSize() const
    {
        return m_vertices[3].position;
    }

    void CImage::setColour(const sf::Color colour)
    {
        for (std::size_t i {0}; i < m_vertices.getVertexCount(); i++)
        {
            m_vertices[i].color = colour;
        }
    }

    sf::Color CImage::getColour() const
    {
        return m_vertices[0].color;
    }

    sf::FloatRect CImage::getLocalBounds() const
    {
        return m_vertices.getBounds();
    }

    void CImage::tick(float deltaTime)
    {
    }

    void CImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = m_texture;
        target.draw(m_vertices, states);
    }

    void CImage::updateTexCoords()
    {
        if (!m_texture) return;
        
        m_vertices[1].texCoords = {0.f, static_cast<float>(m_texture->getSize().y)};
        m_vertices[2].texCoords = {static_cast<float>(m_texture->getSize().x), 0.f};
        m_vertices[3].texCoords = {
            static_cast<float>(m_texture->getSize().x),
            static_cast<float>(m_texture->getSize().y)
        };
    }
}
