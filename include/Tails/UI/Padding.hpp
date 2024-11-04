#ifndef TAILS_PADDING_HPP
#define TAILS_PADDING_HPP

#include <Tails/Config.hpp>

#include <SFML/Graphics/Rect.hpp>

namespace tails
{
    struct TAILS_API SPadding final
    {
        SPadding() : top(0.f), left(0.f), bottom(0.f), right(0.f) {}
        SPadding(float inTop, float inLeft, float inBottom, float inRight)
            : top(inTop), left(inLeft), bottom(inBottom), right(inRight) {}
        explicit SPadding(const sf::FloatRect& floatRect);

        float top;
        float left;
        float bottom;
        float right;
    };
}

#endif // TAILS_PADDING_HPP
