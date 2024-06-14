#ifndef TAILS_ANCHORS_HPP
#define TAILS_ANCHORS_HPP

#include <Tails/Config.hpp>

#include <SFML/System/Vector2.hpp>

namespace tails
{
    struct TAILS_API Anchors
    {
        sf::Vector2f minimum;
        sf::Vector2f maximum;
    };
}

#endif //TAILS_ANCHORS_HPP
