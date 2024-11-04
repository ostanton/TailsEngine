#include <Tails/Components/TileMapComponent.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void CTileMapComponent::setTiles(std::vector<TileType> tiles, bool updateMap /* = true */)
    {
        m_tiles.clear();
        m_tiles.insert(m_tiles.end(), tiles.begin(), tiles.end());
        if (updateMap)
            update();
    }

    void CTileMapComponent::setMapSize(const sf::Vector2u& size, bool updateMap /* = false */)
    {
        m_mapSize = size;
        if (updateMap)
            update();
    }

    void CTileMapComponent::setMapTexture(const sf::Texture* tileMap, bool updateMap /* = false */)
    {
        m_texture = tileMap;
        if (updateMap)
            update();
    }

    void CTileMapComponent::setTileSize(size_t size, bool updateMap /* = false */)
    {
        m_tileSize = size;
        if (updateMap)
            update();
    }

    sf::FloatRect CTileMapComponent::getGlobalBounds() const
    {
        return {m_vertices[0].position, m_vertices[3].position};
    }

    void CTileMapComponent::update()
    {
        if (!m_texture || m_tiles.empty() || m_tileSize == 0 || m_mapSize.x == 0 || m_mapSize.y == 0)
            return;

        m_vertices.resize(
            static_cast<size_t>(m_mapSize.x) * static_cast<size_t>(m_mapSize.y) * 4
        );
        
        for (size_t x {0}; x < m_mapSize.x; x++)
        {
            for (size_t y {0}; y < m_mapSize.y; y++)
            {
                size_t tileNum = m_tiles[x + y * m_mapSize.x];
                
                size_t textureU {tileNum % (m_texture->getSize().x / m_tileSize)};
                size_t textureV {tileNum / (m_texture->getSize().x / m_tileSize)};

                sf::Vertex* quad {&m_vertices[(x + y * m_mapSize.x) * 4]};

                quad[0].position = sf::Vector2f(
                    static_cast<float>(x * m_tileSize),
                    static_cast<float>(y * m_tileSize)
                );
                quad[1].position = sf::Vector2f(
                    static_cast<float>((x + 1) * m_tileSize),
                    static_cast<float>(y * m_tileSize)
                );
                quad[2].position = sf::Vector2f(
                    static_cast<float>(x * m_tileSize),
                    static_cast<float>((y + 1) * m_tileSize)
                );
                quad[3].position = sf::Vector2f(
                    static_cast<float>((x + 1) * m_tileSize),
                    static_cast<float>((y + 1) * m_tileSize)
                );

                quad[0].texCoords = sf::Vector2f(
                    static_cast<float>(textureU * m_tileSize),
                    static_cast<float>(textureV * m_tileSize)
                );
                quad[1].texCoords = sf::Vector2f(
                    static_cast<float>((textureU + 1) * m_tileSize),
                    static_cast<float>(textureV * m_tileSize)
                );
                quad[2].texCoords = sf::Vector2f(
                    static_cast<float>(textureU * m_tileSize),
                    static_cast<float>((textureV + 1) * m_tileSize)
                );
                quad[3].texCoords = sf::Vector2f(
                    static_cast<float>((textureU + 1) * m_tileSize),
                    static_cast<float>((textureV + 1) * m_tileSize)
                );
            }
        }
    }

    void CTileMapComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        CComponent::draw(target, states);
        
        states.transform *= getTransform();
        states.texture = m_texture;
        target.draw(m_vertices, states);
    }
}
