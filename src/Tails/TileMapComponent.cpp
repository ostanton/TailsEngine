#include <Tails/TileMapComponent.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void CTileMapComponent::setTileMap(const sf::Texture* tileMap)
    {
        m_tileMap = tileMap;
        update();
    }

    void CTileMapComponent::setTileSize(size_t size)
    {
        m_tileSize = size;
        update();
    }

    sf::FloatRect CTileMapComponent::getGlobalBounds() const
    {
        return {m_vertices[0].position, m_vertices[3].position};
    }

    void CTileMapComponent::update()
    {
        const unsigned int tileMapWidth {m_tileMap->getSize().x};
        const float tileCount {static_cast<float>(tileMapWidth) / static_cast<float>(m_tileSize)};
    }

    void CTileMapComponent::tick(float deltaTime)
    {
        
    }

    void CTileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = m_tileMap;
        target.draw(m_vertices, states);
    }
}
