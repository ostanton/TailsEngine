#include <Tails/UI/RectangleWidget.hpp>

namespace tails
{
    void RectangleWidget::setSize(const sf::Vector2f& size)
    {
        Widget::setSize(size);

        m_rectangle.setSize(size);
    }
}
