#include <Tails/Input/Keys.hpp>

namespace tails
{
    bool Key::isPressed() const
    {
        return sf::Keyboard::isKeyPressed(key);
    }

    const Key& Keys::getKeyFromString(const std::string& string)
    {
        if (string == "Up")
            return Up;

        return Unknown;
    }
} // tails
