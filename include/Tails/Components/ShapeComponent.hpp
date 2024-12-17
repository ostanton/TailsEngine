#ifndef TAILS_SHAPE_COMPONENT_HPP
#define TAILS_SHAPE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/Components/TransformComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace sf
{
    class Texture;
    class Shape;
}

namespace tails
{
    /**
     * Abstract base class wrapper for SFML shape classes
     */
    class TAILS_API CShapeComponent : public CTransformComponent
    {
    public:
        virtual void setTexture(const sf::Texture* texture, bool resetRect = false) = 0;
        [[nodiscard]] virtual const sf::Texture* getTexture() const = 0;

        virtual void setTextureRect(const sf::IntRect& rect) = 0;
        [[nodiscard]] virtual const sf::IntRect& getTextureRect() const = 0;

        [[nodiscard]] virtual sf::Shape& getShape() = 0;
        [[nodiscard]] virtual const sf::Shape& getShape() const = 0;
    };
}

#endif // TAILS_SHAPE_COMPONENT_HPP
