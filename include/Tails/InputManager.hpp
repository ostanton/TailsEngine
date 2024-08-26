#ifndef TAILS_INPUTMANAGER_HPP
#define TAILS_INPUTMANAGER_HPP

#include <Tails/Config.hpp>

#include <SFML/Window/Joystick.hpp>

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
        LB,
        RB,
        Select,
        Start,
        LS,
        RS
    };

    /**
     * Xbox-specific axes mapped to SFML Joystick axes
     */
    enum class TAILS_API EXboxAxis : int
    {
        DPadX = sf::Joystick::PovX,
        DPadY = sf::Joystick::PovY,
        LT = sf::Joystick::Z,
        RT = sf::Joystick::Z,
        LeftThumbstickX = sf::Joystick::X,
        LeftThumbstickY = sf::Joystick::Y,
        RightThumbstickX = sf::Joystick::U,
        RightThumbstickY = sf::Joystick::V
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

        /**
         * The key type, normally set via EInputDevice, i.e. keyboard, mouse, etc.
         */
        int device {0};

        /**
         * The button itself, i.e. on keyboard: 0 = A, 1 = B, etc.
         * Can be set from sf::Keyboard::Key, sf::Mouse::Button, etc.
         */
        int code {0};

        void setDevice(EInputDevice inDevice);

        [[nodiscard]] bool isPressed() const;

        static EInputDevice inputDeviceFromString(const std::string& device);
        static std::string stringFromInputDevice(EInputDevice device);
    };

    struct TAILS_API SKeyAxis : SKey
    {
        SKeyAxis(EInputDevice inDevice, int inCode, float inScaleMultiplier);
        SKeyAxis(EInputDevice inDevice, EXboxAxis axis, float inScaleMultiplier);
        SKeyAxis(EInputDevice inDevice, EXboxButton button, float inScaleMultiplier);
        
        float scaleMultiplier {1.f};
        float deadZone {0.1f};

        // hack to stop A (= 0) from being isPressed when we want LeftThumbstickX (= 0) scalar value
        bool isScalar {false};

        [[nodiscard]] float getScalarAmount() const;
        [[nodiscard]] bool isActive() const;
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
        [[nodiscard]] static bool isActionPressed(const std::string& action);

        [[nodiscard]] static bool isAxisActive(const std::string& axis);
        [[nodiscard]] static float getAxisValue(const std::string& axis);

        static void addActionMapping(std::string name, SKey key);
        static void addActionMapping(std::string name, const std::vector<SKey>& keys);

        static void addAxisMapping(std::string name, SKeyAxis key);
        static void addAxisMapping(std::string name, const std::vector<SKeyAxis>& keys);

        [[nodiscard]] static bool actionExists(const std::string& action);
        [[nodiscard]] static bool axisExists(const std::string& axis);
        
    private:
        static CInputManager& get();

        std::unordered_map<std::string, std::vector<SKey>> m_actions;
        std::unordered_map<std::string, std::vector<SKeyAxis>> m_axes;
    };
}

#endif // TAILS_INPUTMANAGER_HPP
