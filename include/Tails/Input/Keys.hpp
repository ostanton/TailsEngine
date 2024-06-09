#ifndef TAILS_KEYS_HPP
#define TAILS_KEYS_HPP

#include <string>

namespace tails
{
    // key struct that holds data about a specific key that was pressed, etc.
    // should be passed by const ref much like a string would, because it's basically
    // a wrapper for string at the moment. It should encapsulate SFML's sf::Keyboard::Key
    // enum also if possible, and maybe joystick stuff.
    struct Key
    {
        Key() = default;

        constexpr Key(const std::string& inName)
            : name(inName) {}

        constexpr Key(const Key& other)
        {
            name = other.name;
        }

        constexpr Key(Key&& other)
        {
            name = std::move(other.name);
        }

        constexpr Key& operator=(const Key& other)
        {
            name = other.name;
            return *this;
        }

        constexpr Key& operator=(Key&& other)
        {
            name = std::move(other.name);
            return *this;
        }

        std::string name;
    };

    // const static list of keys and probably controller inputs
    struct Keys
    {
        constexpr static Key Space {"Space"};
        constexpr static Key A {"A"};
    };
}

#endif // TAILS_KEYS_HPP
