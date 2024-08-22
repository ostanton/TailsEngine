#include <Tails/Padding.hpp>

namespace tails
{
    SPadding::SPadding(const sf::FloatRect& floatRect)
        : top(floatRect.top), left(floatRect.left), bottom(floatRect.height), right(floatRect.width)
    {
    }
}
