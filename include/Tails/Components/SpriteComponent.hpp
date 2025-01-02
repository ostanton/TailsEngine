#ifndef TAILS_SPRITE_COMPONENT_HPP
#define TAILS_SPRITE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/VertexArray.hpp>

namespace sf
{
    class Texture;
}

namespace tails
{
    class CTexture;
    
    class TAILS_API CSpriteComponent : public CTransformComponent
    {
    public:
        CSpriteComponent();
        ~CSpriteComponent() override;
        
        void setTexture(const std::shared_ptr<CTexture>& texture);
        [[nodiscard]] std::shared_ptr<CTexture> getTexture() const;

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
        std::shared_ptr<CTexture> m_texture;
        const sf::Texture* m_underlying {nullptr};
    };
}
TAILS_REGISTER_CLASS_CUSTOM_NAME(CSpriteComponent, "SpriteComponent")

#endif // TAILS_SPRITE_COMPONENT_HPP
