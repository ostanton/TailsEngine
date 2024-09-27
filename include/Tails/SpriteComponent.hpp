#ifndef TAILS_SPRITE_COMPONENT_HPP
#define TAILS_SPRITE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Component.hpp>

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
        
        void setTexture(sf::Texture* texture);
        [[nodiscard]] sf::Texture* getTexture() const {return m_texture;}

        void setSize(const sf::Vector2f& size);
        [[nodiscard]] const sf::Vector2f& getSize() const;

        void setColour(sf::Color colour);
        [[nodiscard]] sf::Color getColour() const;

    protected:
        void serialise(nlohmann::json& obj) const override;
        void deserialise(const nlohmann::json& obj) override;

        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        [[nodiscard]] sf::FloatRect getGlobalBounds() const override;
        
        sf::VertexArray m_vertices {sf::PrimitiveType::TriangleStrip, 4};
        sf::Texture* m_texture {nullptr};
    };
}
TAILS_REGISTER_CLASS(CSpriteComponent)

#endif // TAILS_SPRITE_COMPONENT_HPP
