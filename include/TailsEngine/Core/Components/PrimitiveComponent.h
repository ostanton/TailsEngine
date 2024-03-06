#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "TailsEngine/Core/Component.h"

namespace tails
{
/**
 * \brief A component which contains a transform and draws. Useful for anything that should exist in the world
 */
class PrimitiveComponent : public Component, public sf::Drawable, public sf::Transformable
{
public:
    virtual sf::FloatRect getLocalBounds() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
};

}
