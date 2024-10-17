#ifndef TAILS_CIRCLE_SHAPE_COMPONENT_HPP
#define TAILS_CIRCLE_SHAPE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/ShapeComponent.hpp>

#include <SFML/Graphics/CircleShape.hpp>

namespace tails
{
    /**
     * Wrapper around SFML's CircleShape
     */
    class TAILS_API CCircleShapeComponent : public CShapeComponent
    {
    public:
        CCircleShapeComponent(float radius = 8.f, size_t pointCount = 16);

        void setRadius(float radius);
        [[nodiscard]] float getRadius() const;

        void setPointCount(size_t count);
        [[nodiscard]] size_t getPointCount() const;

        [[nodiscard]] sf::Vector2f getPoint(size_t index) const;
        [[nodiscard]] sf::Vector2f getCentre() const;

        sf::FloatRect getGlobalBounds() const override;

        void setTexture(const sf::Texture* texture, bool resetRect = false) override;
        [[nodiscard]] const sf::Texture* getTexture() const override;

        void setTextureRect(const sf::IntRect& rect) override;
        [[nodiscard]] const sf::IntRect& getTextureRect() const override;

        [[nodiscard]] sf::Shape& getShape() override {return m_circleShape;}
        [[nodiscard]] const sf::Shape& getShape() const override {return m_circleShape;}
        
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::CircleShape m_circleShape;
    };
}
TAILS_REGISTER_CLASS(CCircleShapeComponent)

#endif // TAILS_CIRCLE_SHAPE_COMPONENT_HPP
