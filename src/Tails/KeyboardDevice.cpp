#include <Tails/KeyboardDevice.hpp>

#include <SFML/Window/Keyboard.hpp>

namespace tails
{
    bool CKeyboardDevice::isButtonPressed(int button)
    {
        return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(button));
    }
}
