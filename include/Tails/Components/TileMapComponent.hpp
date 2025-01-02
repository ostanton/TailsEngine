#ifndef TAILS_TILE_MAP_COMPONENT_HPP
#define TAILS_TILE_MAP_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include <vector>

namespace sf
{
    class Texture;
}

namespace tails
{
    class CTexture;
    
    class TAILS_API CTileMapComponent final : public CTransformComponent
    {
    public:
        using TileType = size_t;
        
        void setTiles(std::vector<TileType> tiles, bool updateMap = true);
        [[nodiscard]] const std::vector<TileType>& getTiles() const {return m_tiles;}
        
        void setMapSize(const sf::Vector2u& size, bool updateMap = false);
        [[nodiscard]] const sf::Vector2u& getMapSize() const {return m_mapSize;}
        
        void setMapTexture(const std::shared_ptr<CTexture>& tileMap, bool updateMap = false);
        [[nodiscard]] std::shared_ptr<CTexture> getMapTexture() const;

        void setTileSize(size_t size, bool updateMap = false);
        [[nodiscard]] size_t getTileSize() const {return m_tileSize;}

        sf::FloatRect getGlobalBounds() const override;
        
    private:
        void update();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        std::vector<TileType> m_tiles;
        std::shared_ptr<CTexture> m_texture;
        const sf::Texture* m_underlying {nullptr};
        size_t m_tileSize {16};
        sf::Vector2u m_mapSize;
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip};
    };
}
TAILS_REGISTER_CLASS_CUSTOM_NAME(CTileMapComponent, "TileMapComponent")

#endif // TAILS_TILE_MAP_COMPONENT_HPP
