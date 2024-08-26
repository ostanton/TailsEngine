#include <Tails/InputManager.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace tails
{
    SKey::SKey(EInputDevice inDevice, int inCode)
        : device(static_cast<int>(inDevice)), code(inCode)
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxButton button)
        : SKey(inDevice, static_cast<int>(button))
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxAxis axis)
        : device(static_cast<int>(inDevice)), code(static_cast<int>(axis)), scalar(true)
    {
    }

    void SKey::setDevice(EInputDevice inDevice)
    {
        device = static_cast<int>(inDevice);
    }

    bool SKey::isPressed() const
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

    float SKey::getScalarAmount() const
    {
        return sf::Joystick::getAxisPosition(0, static_cast<sf::Joystick::Axis>(code)) * 0.01f;
    }

    bool SKey::isScalarActive() const
    {
        return getScalarAmount() >= deadzone || getScalarAmount() <= -deadzone;
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

    bool CInputManager::isActionActive(const std::string& action)
    {
        return isActionPressed(action) || isActionScalarActive(action);
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

    void CInputManager::addKeyToAction(const std::string& action, const SKey key)
    {
        if (actionExists(action))
            get().m_actions[action].push_back(key);
    }

    bool CInputManager::actionExists(const std::string& action)
    {
        return get().m_actions.contains(action);
    }

    float CInputManager::getActionScalarAmount(const std::string& action)
    {
        if (!actionExists(action)) return 0.f;

        float amount {0.f};

        for (auto& key : get().m_actions[action])
        {
            if (std::abs(key.getScalarAmount()) > amount)
                amount = key.getScalarAmount();
        }

        return amount;
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
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

    bool CInputManager::isActionScalarActive(const std::string& action)
    {
        for (auto& [actionName, values] : get().m_actions)
        {
            if (actionName == action)
            {
                for (auto& key : values)
                {
                    if (key.isScalarActive())
                        return true;
                }
            }
        }

        return false;
    }
}
