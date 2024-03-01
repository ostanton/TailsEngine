#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "Widget.h"

namespace tails
{
class RectWidget : public sf::RectangleShape, public Widget
{
public:
    RectWidget();
};

}
