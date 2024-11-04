#ifndef TAILS_SPRITE_COMPONENT_HPP
#define TAILS_SPRITE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/Component.hpp>

#include <SFML/Graphics/VertexArray.hpp>

namespace sf
{
    class Texture;
}

namespace tails
{
    class TAILS_API CSpriteComponent : public CComponent
    {
    public:
        CSpriteComponent();
        
        void setTexture(const sf::Texture* texture);
        [[nodiscard]] const sf::Texture* getTexture() const {return m_texture;}

        void setTextureCoords(const sf::Rect<unsigned int>& coords);
        [[nodiscard]] sf::Rect<unsigned int> getTextureCoords() const;

        void setSize(const sf::Vector2f& size);
        [[nodiscard]] const sf::Vector2f& getSize() const;

        void setColour(sf::Color colour);
        [[nodiscard]] sf::Color getColour() const;
        
        [[nodiscard]] sf::FloatRect getGlobalBounds() const override;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip, 4};
        const sf::Texture* m_texture {nullptr};
    };
}
TAILS_REGISTER_CLASS(CSpriteComponent)

#endif // TAILS_SPRITE_COMPONENT_HPP
