#ifndef TAILS_MARGIN_HPP
#define TAILS_MARGIN_HPP

#include <Tails/Config.hpp>

namespace tails
{
    struct TAILS_API Margin
    {
        float left {0.f}, top {0.f}, right {0.f}, bottom {0.f};

        Margin() = default;
        Margin(const Margin& margin) = default;

        Margin(float l, float t, float r, float b)
        : left(l), top(t), right(r), bottom(b) {}

        Margin(const sf::Vector2f& horizontal, const sf::Vector2f& vertical)
        : left(horizontal.x), top(vertical.x), right(horizontal.y), bottom(vertical.y) {}
    };
}

#endif //TAILS_MARGIN_HPP
