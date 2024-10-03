#include <Tails/CircleShapeComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CCircleShapeComponent::CCircleShapeComponent(float radius, size_t pointCount)
        : m_circleShape(radius, pointCount)
    {
    }

    void CCircleShapeComponent::setRadius(float radius)
    {
        m_circleShape.setRadius(radius);
    }

    float CCircleShapeComponent::getRadius() const
    {
        return m_circleShape.getRadius();
    }

    void CCircleShapeComponent::setPointCount(size_t count)
    {
        m_circleShape.setPointCount(count);
    }

    size_t CCircleShapeComponent::getPointCount() const
    {
        return m_circleShape.getPointCount();
    }

    sf::Vector2f CCircleShapeComponent::getPoint(size_t index) const
    {
        return m_circleShape.getPoint(index);
    }

    sf::Vector2f CCircleShapeComponent::getCentre() const
    {
        return m_circleShape.getGeometricCenter();
    }

    sf::FloatRect CCircleShapeComponent::getGlobalBounds() const
    {
        return m_circleShape.getGlobalBounds();
    }

    void CCircleShapeComponent::setTexture(const sf::Texture* texture, bool resetRect)
    {
        m_circleShape.setTexture(texture, resetRect);
    }

    const sf::Texture* CCircleShapeComponent::getTexture() const
    {
        return m_circleShape.getTexture();
    }

    void CCircleShapeComponent::setTextureRect(const sf::IntRect& rect)
    {
        m_circleShape.setTextureRect(rect);
    }

    const sf::IntRect& CCircleShapeComponent::getTextureRect() const
    {
        return m_circleShape.getTextureRect();
    }

    void CCircleShapeComponent::tick(float deltaTime)
    {
        
    }

    void CCircleShapeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_circleShape, states);
    }
}
