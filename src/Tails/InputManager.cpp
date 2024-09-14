#include <Tails/InputManager.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace tails
{
    SKey::SKey(EInputDevice inDevice, int inCode, float inScaleMultiplier)
        : device(static_cast<int>(inDevice)), code(inCode), scaleMultiplier(inScaleMultiplier)
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxButton button, float inScaleMultiplier)
        : SKey(inDevice, static_cast<int>(button), inScaleMultiplier)
    {
    }

    SKey::SKey(EInputDevice inDevice, EXboxAxis axis, float inScaleMultiplier)
        : SKey(inDevice, static_cast<int>(axis), inScaleMultiplier)
    {
        isScalar = true;
    }

    SKey::SKey(EInputDevice inDevice, sf::Keyboard::Key key, float inScaleMultiplier)
        : SKey(inDevice, static_cast<int>(key), inScaleMultiplier)
    {
    }

    SKey::SKey(EInputDevice inDevice, sf::Mouse::Button button, float inScaleMultiplier)
        : SKey(inDevice, static_cast<int>(button), inScaleMultiplier)
    {
    }

    void SKey::setDevice(EInputDevice inDevice)
    {
        device = static_cast<int>(inDevice);
    }

    float SKey::getScalarAmount() const
    {
        switch (device)
        {
        case static_cast<int>(EInputDevice::Keyboard):
            if (isKeyPressed(static_cast<sf::Keyboard::Key>(code))) return scaleMultiplier;
            break;
        case static_cast<int>(EInputDevice::Mouse):
            if (isButtonPressed(static_cast<sf::Mouse::Button>(code))) return scaleMultiplier;
            break;
        case static_cast<int>(EInputDevice::Controller):
            if (isScalar)
                return getAxisPosition(0, static_cast<sf::Joystick::Axis>(code)) * 0.01f * scaleMultiplier;
            if (sf::Joystick::isButtonPressed(0, code)) return scaleMultiplier;
            break;
        default:
            break;
        }

        return 0.f;
    }

    bool SKey::isActive() const
    {
        return std::abs(getScalarAmount()) >= deadZone;
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
        for (auto& [actionName, values] : get().m_actions)
        {
            if (actionName == action)
            {
                for (auto& key : values)
                {
                    if (key.isActive())
                        return true;
                }
            }
        }

        return false;
    }

    float CInputManager::getActionScalarValue(const std::string& action)
    {
        if (!actionExists(action)) return 0.f;

        float result {0.f};

        for (auto& axisKey : get().m_actions[action])
        {
            result += axisKey.getScalarAmount();
        }

        return result;
    }

    void CInputManager::addActionMapping(std::string name, SKey key)
    {
        addActionMapping(std::move(name), std::vector({key}));
    }

    void CInputManager::addActionMapping(std::string name, const std::vector<SKey>& keys)
    {
        if (actionExists(name))
            get().m_actions[name] = keys;
        else
            get().m_actions.try_emplace(std::move(name), keys);
    }

    bool CInputManager::actionExists(const std::string& action)
    {
        return get().m_actions.contains(action);
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
    }
}
