#ifndef TAILS_TILE_MAP_COMPONENT_HPP
#define TAILS_TILE_MAP_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Component.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

namespace sf
{
    class Texture;
}

namespace tails
{
    class TAILS_API CTileMapComponent final : public CComponent
    {
    public:
        using TileType = size_t;
        
        void setTiles(std::vector<TileType> tiles, bool updateMap = true);
        [[nodiscard]] const std::vector<TileType>& getTiles() const {return m_tiles;}
        
        void setMapSize(const sf::Vector2u& size, bool updateMap = false);
        [[nodiscard]] const sf::Vector2u& getMapSize() const {return m_mapSize;}
        
        void setMapTexture(const sf::Texture* tileMap, bool updateMap = false);
        [[nodiscard]] const sf::Texture* setMapTexture() const {return m_texture;}

        void setTileSize(size_t size, bool updateMap = false);
        [[nodiscard]] size_t getTileSize() const {return m_tileSize;}

        sf::FloatRect getGlobalBounds() const override;
        
    private:
        void update();

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        std::vector<TileType> m_tiles;
        const sf::Texture* m_texture {nullptr};
        size_t m_tileSize {16};
        sf::Vector2u m_mapSize;
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip};
    };
}
TAILS_REGISTER_CLASS(CTileMapComponent)

#endif // TAILS_TILE_MAP_COMPONENT_HPP
