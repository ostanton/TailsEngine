#include <Tails/Key.hpp>

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

        if (name == "Up") return {EInputDevice::Keyboard, sf::Keyboard::Key::Up};
        if (name == "Down") return {EInputDevice::Keyboard, sf::Keyboard::Key::Down};
        if (name == "Left") return {EInputDevice::Keyboard, sf::Keyboard::Key::Left};
        if (name == "Right") return {EInputDevice::Keyboard, sf::Keyboard::Key::Right};

        /* CONTROLLER */
        if (name == "Controller A") return {EInputDevice::Controller, EXboxButton::A};
        
        if (name == "D-pad X") return {EInputDevice::Controller, EXboxAxis::DPadX};
        if (name == "D-pad Y") return {EInputDevice::Controller, EXboxAxis::DPadY};

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
