#ifndef TAILS_RECTANGLEWIDGET_HPP
#define TAILS_RECTANGLEWIDGET_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/Widget.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace tails
{
    class TAILS_API RectangleWidget : public Widget
    {
    public:
        void setSize(const sf::Vector2f& size) override;

        sf::RectangleShape& getRectangle() {return m_rectangle;}

    protected:
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}

    private:
        sf::RectangleShape m_rectangle;
    };
}

#endif // TAILS_RECTANGLEWIDGET_HPP
