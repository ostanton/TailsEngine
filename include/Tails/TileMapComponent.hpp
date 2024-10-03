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
    struct TAILS_API STile final
    {
        /**
         * The rectangle on the tile map that actually represents this tile
         */
        sf::Rect<unsigned int> textureRect;
        
        /**
         * The position of this tile relative to the tile map component
         */
        sf::Vector2f mapPosition;
    };
    
    class TAILS_API CTileMapComponent final : public CComponent
    {
    public:
        void setTileMap(const sf::Texture* tileMap);
        [[nodiscard]] const sf::Texture* getTileMap() const {return m_tileMap;}

        void setTileSize(size_t size);
        [[nodiscard]] size_t getTileSize() const {return m_tileSize;}

        sf::FloatRect getGlobalBounds() const override;
        
    private:
        void update();

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        std::vector<STile> m_tiles;
        const sf::Texture* m_tileMap {nullptr};
        size_t m_tileSize {16};
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip};
    };
}

#endif // TAILS_TILE_MAP_COMPONENT_HPP
