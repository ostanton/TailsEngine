#ifndef TAILS_CONVEX_SHAPE_COMPONENT_HPP
#define TAILS_CONVEX_SHAPE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/ShapeComponent.hpp>

#include <SFML/Graphics/ConvexShape.hpp>

namespace tails
{
    /**
     * Wrapper around SFML's ConvexShape
     */
    class TAILS_API CConvexShapeComponent : public CShapeComponent
    {
    public:
        CConvexShapeComponent(size_t pointCount = 0);

        void setPointCount(size_t count);
        [[nodiscard]] size_t getPointCount() const;

        void setPoint(size_t index, const sf::Vector2f& point);
        [[nodiscard]] sf::Vector2f getPoint(size_t index) const;

        sf::FloatRect getLocalBounds() const override;

        void setTexture(const sf::Texture* texture, bool resetRect = false) override;
        [[nodiscard]] const sf::Texture* getTexture() const override;

        void setTextureRect(const sf::IntRect& rect) override;
        [[nodiscard]] const sf::IntRect& getTextureRect() const override;

        [[nodiscard]] sf::Shape& getShape() override {return m_convexShape;}
        [[nodiscard]] const sf::Shape& getShape() const override {return m_convexShape;}
        
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::ConvexShape m_convexShape;
    };
}
TAILS_REGISTER_CLASS_CUSTOM_NAME(CConvexShapeComponent, "ConvexShapeComponent")

#endif // TAILS_CONVEX_SHAPE_COMPONENT_HPP
