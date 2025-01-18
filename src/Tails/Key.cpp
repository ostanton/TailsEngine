#include <Tails/Key.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    SKey::SKey(EInputDevice inDevice, int inCode)
        : device(inDevice), code(inCode)
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxButton button)
        : SKey(inDevice, static_cast<int>(button))
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxAxis axis)
        : SKey(inDevice, static_cast<int>(axis))
    {
        isScalar = true;
    }

    SKey::SKey(EInputDevice inDevice, sf::Keyboard::Key key)
        : SKey(inDevice, static_cast<int>(key))
    {
    }

    SKey::SKey(EInputDevice inDevice, sf::Mouse::Button button)
        : SKey(inDevice, static_cast<int>(button))
    {
    }
    
    EInputDevice SKey::inputDeviceFromString(const std::string& device)
    {
        if (device == "Keyboard" || device == "keyboard")
            return EInputDevice::Keyboard;
        if (device == "Mouse" || device == "mouse")
            return EInputDevice::Mouse;
        if (device == "Controller" || device == "controller")
            return EInputDevice::Controller;

        return EInputDevice::Unknown;
    }

    std::string SKey::stringFromInputDevice(EInputDevice device)
    {
        switch (device)
        {
        case EInputDevice::Keyboard:
            return "Keyboard";
        case EInputDevice::Mouse:
            return "Mouse";
        case EInputDevice::Controller:
            return "Controller";
        default:
            break;
        }

        return "Unknown";
    }

    SKey SKey::getKeyFromString(std::string_view name)
    {
        /* KEYBOARD */
        if (name == "A") return {EInputDevice::Keyboard, sf::Keyboard::Key::A};
        if (name == "B") return {EInputDevice::Keyboard, sf::Keyboard::Key::B};
        if (name == "C") return {EInputDevice::Keyboard, sf::Keyboard::Key::C};
        if (name == "D") return {EInputDevice::Keyboard, sf::Keyboard::Key::D};
        if (name == "E") return {EInputDevice::Keyboard, sf::Keyboard::Key::E};
        if (name == "F") return {EInputDevice::Keyboard, sf::Keyboard::Key::F};
        if (name == "G") return {EInputDevice::Keyboard, sf::Keyboard::Key::G};
        if (name == "H") return {EInputDevice::Keyboard, sf::Keyboard::Key::H};
        if (name == "I") return {EInputDevice::Keyboard, sf::Keyboard::Key::I};
        if (name == "J") return {EInputDevice::Keyboard, sf::Keyboard::Key::J};
        if (name == "K") return {EInputDevice::Keyboard, sf::Keyboard::Key::K};
        if (name == "L") return {EInputDevice::Keyboard, sf::Keyboard::Key::L};
        if (name == "M") return {EInputDevice::Keyboard, sf::Keyboard::Key::M};
        if (name == "N") return {EInputDevice::Keyboard, sf::Keyboard::Key::N};
        if (name == "O") return {EInputDevice::Keyboard, sf::Keyboard::Key::O};
        if (name == "P") return {EInputDevice::Keyboard, sf::Keyboard::Key::P};
        if (name == "Q") return {EInputDevice::Keyboard, sf::Keyboard::Key::Q};
        if (name == "R") return {EInputDevice::Keyboard, sf::Keyboard::Key::R};
        if (name == "S") return {EInputDevice::Keyboard, sf::Keyboard::Key::S};
        if (name == "T") return {EInputDevice::Keyboard, sf::Keyboard::Key::T};
        if (name == "U") return {EInputDevice::Keyboard, sf::Keyboard::Key::U};
        if (name == "V") return {EInputDevice::Keyboard, sf::Keyboard::Key::V};
        if (name == "W") return {EInputDevice::Keyboard, sf::Keyboard::Key::W};
        if (name == "X") return {EInputDevice::Keyboard, sf::Keyboard::Key::X};
        if (name == "Y") return {EInputDevice::Keyboard, sf::Keyboard::Key::Y};
        if (name == "Z") return {EInputDevice::Keyboard, sf::Keyboard::Key::Z};

        if (name == "0") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num0};
        if (name == "1") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num1};
        if (name == "2") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num2};
        if (name == "3") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num3};
        if (name == "4") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num4};
        if (name == "5") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num5};
        if (name == "6") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num6};
        if (name == "7") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num7};
        if (name == "8") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num8};
        if (name == "9") return {EInputDevice::Keyboard, sf::Keyboard::Key::Num9};

        if (name == "Escape") return {EInputDevice::Keyboard, sf::Keyboard::Key::Escape};
        if (name == "Left Control") return {EInputDevice::Keyboard, sf::Keyboard::Key::LControl};
        if (name == "Left Shift") return {EInputDevice::Keyboard, sf::Keyboard::Key::LShift};
        if (name == "Left Alt") return {EInputDevice::Keyboard, sf::Keyboard::Key::LAlt};
        if (name == "Left Command") return {EInputDevice::Keyboard, sf::Keyboard::Key::LSystem};
        if (name == "Right Control") return {EInputDevice::Keyboard, sf::Keyboard::Key::RControl};
        if (name == "Right Shift") return {EInputDevice::Keyboard, sf::Keyboard::Key::RShift};
        if (name == "Right Alt") return {EInputDevice::Keyboard, sf::Keyboard::Key::RAlt};
        if (name == "Right Command") return {EInputDevice::Keyboard, sf::Keyboard::Key::RSystem};
        if (name == "Menu") return {EInputDevice::Keyboard, sf::Keyboard::Key::Menu};
        
        if (name == "[" || name == "Left Square Bracket") return {EInputDevice::Keyboard, sf::Keyboard::Key::LBracket};
        if (name == "]" || name == "Right Square Bracket") return {EInputDevice::Keyboard, sf::Keyboard::Key::RBracket};
        if (name == ";" || name == "Semicolon") return {EInputDevice::Keyboard, sf::Keyboard::Key::Semicolon};
        if (name == "," || name == "Comma") return {EInputDevice::Keyboard, sf::Keyboard::Key::Comma};
        if (name == "." || name == "Full stop" || name == "Period" || name == "Dot")
            return {EInputDevice::Keyboard, sf::Keyboard::Key::Period};
        if (name == "'" || name == "Apostrophe") return {EInputDevice::Keyboard, sf::Keyboard::Key::Apostrophe};
        if (name == "/" || name == "Slash") return {EInputDevice::Keyboard, sf::Keyboard::Key::Slash};
        if (name == "\\" || name == "Backslash") return {EInputDevice::Keyboard, sf::Keyboard::Key::Backslash};
        if (name == "`" || name == "Grave") return {EInputDevice::Keyboard, sf::Keyboard::Key::Grave};
        if (name == "=" || name == "Equal") return {EInputDevice::Keyboard, sf::Keyboard::Key::Equal};
        if (name == "-" || name == "Hyphen") return {EInputDevice::Keyboard, sf::Keyboard::Key::Hyphen};
        
        if (name == "Space" || name == "Space bar") return {EInputDevice::Keyboard, sf::Keyboard::Key::Space};
        if (name == "Enter" || name == "Return") return {EInputDevice::Keyboard, sf::Keyboard::Key::Enter};
        if (name == "Backspace") return {EInputDevice::Keyboard, sf::Keyboard::Key::Backspace};
        if (name == "Tab") return {EInputDevice::Keyboard, sf::Keyboard::Key::Tab};
        if (name == "Page Up") return {EInputDevice::Keyboard, sf::Keyboard::Key::PageUp};
        if (name == "Page Down") return {EInputDevice::Keyboard, sf::Keyboard::Key::PageDown};
        if (name == "End") return {EInputDevice::Keyboard, sf::Keyboard::Key::End};
        if (name == "Home") return {EInputDevice::Keyboard, sf::Keyboard::Key::Home};
        if (name == "Insert") return {EInputDevice::Keyboard, sf::Keyboard::Key::Insert};
        if (name == "Delete") return {EInputDevice::Keyboard, sf::Keyboard::Key::Delete};

        // Add, subtract, etc. if added

        if (name == "Up") return {EInputDevice::Keyboard, sf::Keyboard::Key::Up};
        if (name == "Down") return {EInputDevice::Keyboard, sf::Keyboard::Key::Down};
        if (name == "Left") return {EInputDevice::Keyboard, sf::Keyboard::Key::Left};
        if (name == "Right") return {EInputDevice::Keyboard, sf::Keyboard::Key::Right};

        if (name == "Numpad 0") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad0};
        if (name == "Numpad 1") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad1};
        if (name == "Numpad 2") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad2};
        if (name == "Numpad 3") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad3};
        if (name == "Numpad 4") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad4};
        if (name == "Numpad 5") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad5};
        if (name == "Numpad 6") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad6};
        if (name == "Numpad 7") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad7};
        if (name == "Numpad 8") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad8};
        if (name == "Numpad 9") return {EInputDevice::Keyboard, sf::Keyboard::Key::Numpad9};

        if (name == "F1") return {EInputDevice::Keyboard, sf::Keyboard::Key::F1};
        if (name == "F2") return {EInputDevice::Keyboard, sf::Keyboard::Key::F2};
        if (name == "F3") return {EInputDevice::Keyboard, sf::Keyboard::Key::F3};
        if (name == "F4") return {EInputDevice::Keyboard, sf::Keyboard::Key::F4};
        if (name == "F5") return {EInputDevice::Keyboard, sf::Keyboard::Key::F5};
        if (name == "F6") return {EInputDevice::Keyboard, sf::Keyboard::Key::F6};
        if (name == "F7") return {EInputDevice::Keyboard, sf::Keyboard::Key::F7};
        if (name == "F8") return {EInputDevice::Keyboard, sf::Keyboard::Key::F8};
        if (name == "F9") return {EInputDevice::Keyboard, sf::Keyboard::Key::F9};
        if (name == "F10") return {EInputDevice::Keyboard, sf::Keyboard::Key::F10};
        if (name == "F11") return {EInputDevice::Keyboard, sf::Keyboard::Key::F11};
        if (name == "F12") return {EInputDevice::Keyboard, sf::Keyboard::Key::F12};
        if (name == "F13") return {EInputDevice::Keyboard, sf::Keyboard::Key::F13};
        if (name == "F14") return {EInputDevice::Keyboard, sf::Keyboard::Key::F14};
        if (name == "F15") return {EInputDevice::Keyboard, sf::Keyboard::Key::F15};

        if (name == "Pause") return {EInputDevice::Keyboard, sf::Keyboard::Key::Pause};

        /* CONTROLLER */
        if (name == "Controller Face Button Bottom") return {EInputDevice::Controller, EXboxButton::A};
        if (name == "Controller Face Button Right") return {EInputDevice::Controller, EXboxButton::B};
        if (name == "Controller Face Button Left") return {EInputDevice::Controller, EXboxButton::X};
        if (name == "Controller Face Button Top") return {EInputDevice::Controller, EXboxButton::Y};
        if (name == "Controller Left Thumbstick Button") return {EInputDevice::Controller, EXboxButton::LeftThumbstickButton};
        if (name == "Controller Right Thumbstick Button") return {EInputDevice::Controller, EXboxButton::RightThumbstickButton};
        if (name == "Controller Select") return {EInputDevice::Controller, EXboxButton::Select};
        if (name == "Controller Start") return {EInputDevice::Controller, EXboxButton::Start};
        if (name == "Controller Left Shoulder") return {EInputDevice::Controller, EXboxButton::LeftShoulder};
        if (name == "Controller Right Shoulder") return {EInputDevice::Controller, EXboxButton::RightShoulder};
        
        if (name == "Controller D-pad X") return {EInputDevice::Controller, EXboxAxis::DPadX};
        if (name == "Controller D-pad Y") return {EInputDevice::Controller, EXboxAxis::DPadY};
        if (name == "Controller Left Trigger") return {EInputDevice::Controller, EXboxAxis::LeftTrigger};
        if (name == "Controller Right Trigger") return {EInputDevice::Controller, EXboxAxis::RightTrigger};
        if (name == "Controller Left Thumbstick X") return {EInputDevice::Controller, EXboxAxis::LeftThumbstickX};
        if (name == "Controller Left Thumbstick Y") return {EInputDevice::Controller, EXboxAxis::LeftThumbstickY};
        if (name == "Controller Right Thumbstick X") return {EInputDevice::Controller, EXboxAxis::RightThumbstickX};
        if (name == "Controller Right Thumbstick Y") return {EInputDevice::Controller, EXboxAxis::RightThumbstickY};

        debug::print("Failed to find key \"", name, "\"");
        return {EInputDevice::Unknown, 0};
    }

    SUserKey::SUserKey(std::string_view keyName, float inScaleMultiplier, float inDeadZone)
        : key(SKey::getKeyFromString(keyName)), scaleMultiplier(inScaleMultiplier), deadZone(inDeadZone)
    {
    }

    SUserKey::SUserKey(const SKey& inKey, float inScaleMultiplier, float inDeadZone)
        : key(inKey), scaleMultiplier(inScaleMultiplier), deadZone(inDeadZone)
    {
    }

    float SUserKey::getScalarAmount() const
    {
        switch (key.device)
        {
        case EInputDevice::Keyboard:
            if (isKeyPressed(static_cast<sf::Keyboard::Key>(key.code))) return scaleMultiplier;
            break;
        case EInputDevice::Mouse:
            if (isButtonPressed(static_cast<sf::Mouse::Button>(key.code))) return scaleMultiplier;
            break;
        case EInputDevice::Controller:
            if (key.isScalar)
                return getAxisPosition(0, static_cast<sf::Joystick::Axis>(key.code)) * 0.01f * scaleMultiplier;
            if (sf::Joystick::isButtonPressed(0, key.code)) return scaleMultiplier;
            break;
        default:
            break;
        }

        return 0.f;
    }

    bool SUserKey::isActive() const
    {
        return std::abs(getScalarAmount()) >= deadZone;
    }
}
