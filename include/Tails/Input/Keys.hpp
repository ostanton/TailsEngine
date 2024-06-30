#ifndef TAILS_KEYS_HPP
#define TAILS_KEYS_HPP

#include <Tails/Config.hpp>

#include <SFML/Window/Keyboard.hpp>

#include <string>

namespace tails
{
    // key struct that holds data about a specific key that was pressed, etc.
    // should be passed by const ref much like a string would, because it's basically
    // a wrapper for string at the moment. It should encapsulate SFML's sf::Keyboard::Key
    // enum also if possible, and maybe joystick stuff.
    struct TAILS_API Key
    {
        Key() = default;

        explicit constexpr Key(const std::string& inName, sf::Keyboard::Key inKey)
            : name(inName), key(inKey) {}

        constexpr Key(const Key& other)
        {
            name = other.name;
            key = other.key;
        }

        constexpr Key(Key&& other) noexcept
        {
            name = std::move(other.name);
            key = other.key;
        }

        constexpr Key& operator=(const Key& other) = default;

        constexpr Key& operator=(Key&& other) noexcept
        {
            name = std::move(other.name);
            key = other.key;
            return *this;
        }

        bool operator==(const Key& other) const
        {
            return name == other.name && key == other.key;
        }

        [[nodiscard]] bool isPressed() const;

        std::string name;
        sf::Keyboard::Key key {sf::Keyboard::Unknown};
    };

    // const static list of keys and probably controller inputs
    struct TAILS_API Keys
    {
        constexpr static Key Space {"Space", sf::Keyboard::Space};
        constexpr static Key A {"A", sf::Keyboard::A};
    };
}

#endif // TAILS_KEYS_HPP
