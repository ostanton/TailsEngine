#include <Tails/Input/Keys.hpp>

namespace tails
{
    bool Key::isPressed() const
    {
        return sf::Keyboard::isKeyPressed(key);
    }
} // tails
