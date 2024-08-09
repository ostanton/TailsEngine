#include <Tails/InputManager.hpp>

#include "SFML/Window/Joystick.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

namespace tails
{
    SKey::SKey(EInputDevice inDevice, int inCode)
        : device(static_cast<int>(inDevice)), code(inCode)
    {
    }

    void SKey::setDevice(EInputDevice inDevice)
    {
        device = static_cast<int>(inDevice);
    }

    bool SKey::isPressed()
    {
        switch (device)
        {
        case static_cast<int>(EInputDevice::Keyboard):
            return sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(code));
        case static_cast<int>(EInputDevice::Mouse):
            return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(code));
        case static_cast<int>(EInputDevice::Controller):
            // support multiple controllers?? Probably not!
            return sf::Joystick::isButtonPressed(0, code);
        default:
            break;
        }

        return false;
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

    bool CInputManager::isActionPressed(const std::string& action)
    {
        for (auto& [actionName, values] : get().m_actions)
        {
            if (actionName == action)
            {
                for (auto& key : values)
                {
                    if (key.isPressed())
                        return true;
                }
            }
        }

        return false;
    }

    void CInputManager::addAction(std::string name, SKey key)
    {
        addAction(std::move(name), std::vector({key}));
    }

    void CInputManager::addAction(std::string name, const std::vector<SKey>& keys)
    {
        if (get().m_actions.contains(name))
            get().m_actions[name] = keys;
        else
            get().m_actions.try_emplace(std::move(name), keys);
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
    }
}
