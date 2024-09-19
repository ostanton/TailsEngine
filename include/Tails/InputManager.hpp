#ifndef TAILS_INPUTMANAGER_HPP
#define TAILS_INPUTMANAGER_HPP

#include <Tails/Config.hpp>

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <vector>
#include <string>
#include <unordered_map>

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
        DPadX = sf::Joystick::Axis::PovX,
        DPadY = sf::Joystick::Axis::PovY,
        LeftTrigger = sf::Joystick::Axis::Z,
        RightTrigger = sf::Joystick::Axis::Z,
        LeftThumbstickX = sf::Joystick::Axis::X,
        LeftThumbstickY = sf::Joystick::Axis::Y,
        RightThumbstickX = sf::Joystick::Axis::U,
        RightThumbstickY = sf::Joystick::Axis::V
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
        SKey(EInputDevice inDevice, int inCode, float inScaleMultiplier = 1.f);
        SKey(EInputDevice inDevice, EXboxButton button, float inScaleMultiplier = 1.f);
        SKey(EInputDevice inDevice, EXboxAxis axis, float inScaleMultiplier = 1.f);
        SKey(EInputDevice inDevice, sf::Keyboard::Key key, float inScaleMultiplier = 1.f);
        SKey(EInputDevice inDevice, sf::Mouse::Button button, float inScaleMultiplier = 1.f);
        SKey(EInputDevice inDevice, int inCode, float inScaleMultiplier, float inDeadZone, bool inIsScaler);

        /**
         * The key type, normally set via EInputDevice, i.e. keyboard, mouse, etc.
         */
        EInputDevice device {0};

        /**
         * The button itself, i.e. on keyboard: 0 = A, 1 = B, etc.
         * Can be set from sf::Keyboard::Key, sf::Mouse::Button, etc.
         */
        int code {0};

        float scaleMultiplier {1.f};
        float deadZone {0.1f};
        bool isScalar {false};

        [[nodiscard]] float getScalarAmount() const;
        [[nodiscard]] bool isActive() const;

        static EInputDevice inputDeviceFromString(const std::string& device);
        static std::string stringFromInputDevice(EInputDevice device);
    };

    class TAILS_API CInputManager final
    {
    public:
        /**
         * Checks whether any key in the given action is either pressed (if button), or active (if scalar).
         * Use this for actions with a mix of buttons and axes
         * @param action The action to check
         * @return If any key bound to the action is "active"
         */
        [[nodiscard]] static bool isActionActive(const std::string& action);
        [[nodiscard]] static float getActionScalarValue(const std::string& action);

        static void addActionMapping(std::string name, SKey key);
        static void addActionMapping(std::string name, const std::vector<SKey>& keys);

        [[nodiscard]] static bool actionExists(const std::string& action);

        static bool loadFromFile(const std::string& filename);
        
    private:
        static CInputManager& get();

        std::unordered_map<std::string, std::vector<SKey>> m_actions;
    };
}

#endif // TAILS_INPUTMANAGER_HPP
