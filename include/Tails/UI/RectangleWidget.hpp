#ifndef TAILS_RECTANGLEWIDGET_HPP
#define TAILS_RECTANGLEWIDGET_HPP

#include <Tails/UI/Widget.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace tails
{
    class TAILS_API RectangleWidget : public Widget
    {
    public:
        void setSize(const sf::Vector2f& size) override;

    private:
        sf::RectangleShape m_rectangle;
    };
}

#endif // TAILS_RECTANGLEWIDGET_HPP
