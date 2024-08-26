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
    struct TAILS_API SKey final
    {
        SKey(EInputDevice inDevice, int inCode);
        // separate constructors for each enum mapping. Could have them not be enum class and instead wrap in a
        // namespace or static class, but that just ain't fun is it?
        SKey(EInputDevice inDevice, EXboxButton button);
        SKey(EInputDevice inDevice, EXboxAxis axis);

        /**
         * The key type, normally set via EInputDevice, i.e. keyboard, mouse, etc.
         */
        int device {0};

        /**
         * The button itself, i.e. on keyboard: 0 = A, 1 = B, etc.
         * Can be set from sf::Keyboard::Key, sf::Mouse::Button, etc.
         */
        int code {0};

        /**
         * Whether this key is a scalar value (controller trigger, thumbstick axis, etc.)
         */
        bool scalar {false};

        /**
         * Scalar amount deadzone. The key is only active if the amount is >= this
         */
        float deadzone {0.1f};

        void setDevice(EInputDevice inDevice);

        [[nodiscard]] bool isPressed() const;
        
        /**
         * Gets the key's scalar amount normalised to -1..1
         * @return Scalar amount
         */
        [[nodiscard]] float getScalarAmount() const;

        /**
         * Checks whether the scalar's amount is beyond the deadzone, making it "active"
         * @return Active
         */
        [[nodiscard]] bool isScalarActive() const;

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
        static bool isActionActive(const std::string& action);

        static void addAction(std::string name, SKey key);
        static void addAction(std::string name, const std::vector<SKey>& keys);

        static void addKeyToAction(const std::string& action, const SKey key);

        static bool actionExists(const std::string& action);

        [[nodiscard]] static float getActionScalarAmount(const std::string& action);
        
    private:
        static CInputManager& get();

        /**
         * Checks whether any of the bound buttons (ignores scalars) are pressed
         * @param action The action to check
         * @return Success
         */
        static bool isActionPressed(const std::string& action);

        /**
         * Checks whether any key's scalar amount in a given action is beyond the specified deadzone for it (ignores buttons)
         * @param action The action to check
         * @return If the scalar amount is beyond the deadzone
         */
        static bool isActionScalarActive(const std::string& action);

        std::unordered_map<std::string, std::vector<SKey>> m_actions;
    };
}

#endif // TAILS_INPUTMANAGER_HPP
