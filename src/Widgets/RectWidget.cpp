#include "TailsEngine/Widgets/RectWidget.h"

tails::RectWidget::RectWidget()
{
    setSize(sf::Vector2f(64.f, 32.f));
    setFillColor(sf::Color::Red);
    setOrigin(32.f, 16.f);
    setPosition(64.f, 32.f);
}
