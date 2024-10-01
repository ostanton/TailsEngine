#ifndef TAILS_KEY_HPP
#define TAILS_KEY_HPP

#include <Tails/Config.hpp>

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace tails
{
    enum class TAILS_API EInputDevice : int
    {
        Unknown,
        Keyboard,
        Mouse,
        Controller,

        Count
    };

    /**
     * Xbox-specific buttons mapped to SFML Joystick codes/buttons
     * @note The D-Pad is not considered a button, but two axes. Use EXboxAxis for that
     */
    enum class TAILS_API EXboxButton : int
    {
        A,
        B,
        X,
        Y,
        LeftThumbstickButton,
        RightThumbstickButton,
        Select,
        Start,
        LeftShoulder,
        RightShoulder
    };

    /**
     * Xbox-specific axes mapped to SFML Joystick axes
     */
    enum class TAILS_API EXboxAxis : int
    {
        DPadX = static_cast<int>(sf::Joystick::Axis::PovX),
        DPadY = static_cast<int>(sf::Joystick::Axis::PovY),
        LeftTrigger = static_cast<int>(sf::Joystick::Axis::Z),
        RightTrigger = static_cast<int>(sf::Joystick::Axis::Z),
        LeftThumbstickX = static_cast<int>(sf::Joystick::Axis::X),
        LeftThumbstickY = static_cast<int>(sf::Joystick::Axis::Y),
        RightThumbstickX = static_cast<int>(sf::Joystick::Axis::U),
        RightThumbstickY = static_cast<int>(sf::Joystick::Axis::V)
    };
    
    /**
     * TODO - Work out how buttons and axes work together.
     * Old unreal way? Action mapping and Axis mapping as two separate lists? Actions just for isPressed stuff,
     * and axes for scalar things? Then you can specify a button (bool input) to be somewhere on the scalar range.
     * Like:
     * SKey moveRightButton {Device::Keyboard, Key::Right, 1.f};
     * SKey moveLeftButton {Device::Keyboard, Key::Left, -1.f};
     */
    struct TAILS_API SKey
    {
        SKey(EInputDevice inDevice, int inCode);
        SKey(EInputDevice inDevice, EXboxButton button);
        SKey(EInputDevice inDevice, EXboxAxis axis);
        SKey(EInputDevice inDevice, sf::Keyboard::Key key);
        SKey(EInputDevice inDevice, sf::Mouse::Button button);

        /**
         * The key type, normally set via EInputDevice, i.e. keyboard, mouse, etc.
         */
        EInputDevice device {0};

        /**
         * The button itself, i.e. on keyboard: 0 = A, 1 = B, etc.
         * Can be set from sf::Keyboard::Key, sf::Mouse::Button, etc.
         */
        int code {0};
        bool isScalar {false};

        static EInputDevice inputDeviceFromString(const std::string& device);
        static std::string stringFromInputDevice(EInputDevice device);
        static SKey getKeyFromString(std::string_view name);
    };

    struct TAILS_API SUserKey
    {
        SUserKey(std::string_view keyName, float inScaleMultiplier = 1.f, float inDeadZone = 1.f);
        SUserKey(const SKey& inKey, float inScaleMultiplier = 1.f, float inDeadZone = 1.f);
        
        SKey key;
        float scaleMultiplier {1.f};
        float deadZone {0.1f};

        [[nodiscard]] float getScalarAmount() const;
        [[nodiscard]] bool isActive() const;
    };
}

#endif // TAILS_KEY_HPP
