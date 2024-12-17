#include <Tails/Components/ConvexShapeComponent.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CConvexShapeComponent::CConvexShapeComponent(size_t pointCount)
        : m_convexShape(pointCount)
    {
    }

    void CConvexShapeComponent::setPointCount(size_t count)
    {
        m_convexShape.setPointCount(count);
    }

    size_t CConvexShapeComponent::getPointCount() const
    {
        return m_convexShape.getPointCount();
    }

    void CConvexShapeComponent::setPoint(size_t index, const sf::Vector2f& point)
    {
        m_convexShape.setPoint(index, point);
    }

    sf::Vector2f CConvexShapeComponent::getPoint(size_t index) const
    {
        return m_convexShape.getPoint(index);
    }

    sf::FloatRect CConvexShapeComponent::getGlobalBounds() const
    {
        return m_convexShape.getGlobalBounds();
    }

    void CConvexShapeComponent::setTexture(const sf::Texture* texture, bool resetRect)
    {
        m_convexShape.setTexture(texture, resetRect);
    }

    const sf::Texture* CConvexShapeComponent::getTexture() const
    {
        return m_convexShape.getTexture();
    }

    void CConvexShapeComponent::setTextureRect(const sf::IntRect& rect)
    {
        m_convexShape.setTextureRect(rect);
    }

    const sf::IntRect& CConvexShapeComponent::getTextureRect() const
    {
        return m_convexShape.getTextureRect();
    }

    void CConvexShapeComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_convexShape, states);

        CTransformComponent::draw(target, states);
    }
}
