#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Widget.h"

namespace tails
{
class TextWidget : public sf::Text, public Widget
{
public:
    TextWidget();
};

}
