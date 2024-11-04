#include <Tails/UI/Padding.hpp>

namespace tails
{
    SPadding::SPadding(const sf::FloatRect& floatRect)
        : top(floatRect.position.y), left(floatRect.position.x), bottom(floatRect.size.y), right(floatRect.size.x)
    {
    }
}
