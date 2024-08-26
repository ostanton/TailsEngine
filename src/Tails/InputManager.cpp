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

    SKeyAxis::SKeyAxis(EInputDevice inDevice, int inCode, float inScaleMultiplier)
        : SKey(inDevice, inCode)
    {
        scaleMultiplier = inScaleMultiplier;
    }

    SKeyAxis::SKeyAxis(EInputDevice inDevice, EXboxAxis axis, float inScaleMultiplier)
        : SKeyAxis(inDevice, static_cast<int>(axis), inScaleMultiplier)
    {
        isScalar = true;
    }

    SKeyAxis::SKeyAxis(EInputDevice inDevice, EXboxButton button, float inScaleMultiplier)
        : SKeyAxis(inDevice, static_cast<int>(button), inScaleMultiplier)
    {
    }

    float SKeyAxis::getScalarAmount() const
    {
        if (isPressed() && !isScalar) return scaleMultiplier;
        
        return sf::Joystick::getAxisPosition(0, static_cast<sf::Joystick::Axis>(code)) * scaleMultiplier * 0.01f;
    }

    bool SKeyAxis::isActive() const
    {
        return std::abs(getScalarAmount()) >= deadZone;
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

    bool CInputManager::isAxisActive(const std::string& axis)
    {
        if (!axisExists(axis)) return false;

        for (auto& axisKey : get().m_axes[axis])
        {
            if (axisKey.isActive())
                return true;
        }

        return false;
    }

    float CInputManager::getAxisValue(const std::string& axis)
    {
        if (!axisExists(axis)) return 0.f;

        float result {0.f};
        SKeyAxis* axisPtr {nullptr};

        /**
         * TODO - instead of getting highest result, get a sum of all of them?
         * To stop right favouring left, etc. and instead just returning 0 if right and left are both down
         */

        for (auto& axisKey : get().m_axes[axis])
        {
            if (const float newResult {std::abs(axisKey.getScalarAmount())}; newResult > result)
            {
                result = newResult;
                axisPtr = &axisKey;
            }
        }

        if (!axisPtr) return 0.f;

        return axisPtr->getScalarAmount();
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

    void CInputManager::addAxisMapping(std::string name, SKeyAxis key)
    {
        addAxisMapping(std::move(name), std::vector({key}));
    }

    void CInputManager::addAxisMapping(std::string name, const std::vector<SKeyAxis>& keys)
    {
        if (axisExists(name))
            get().m_axes[name] = keys;
        else
            get().m_axes.try_emplace(std::move(name), keys);
    }

    bool CInputManager::actionExists(const std::string& action)
    {
        return get().m_actions.contains(action);
    }

    bool CInputManager::axisExists(const std::string& axis)
    {
        return get().m_axes.contains(axis);
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
    }
}
