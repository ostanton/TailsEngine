#include <Tails/InputManager.hpp>
#include <Tails/InputDevice.hpp>
#include <Tails/KeyboardDevice.hpp>

namespace tails
{
    bool SAction::isDeviceButtonPressed(IInputDevice& device) const
    {
        for (auto button : buttons)
        {
            if (device.isButtonPressed(button))
                return true;
        }

        return false;
    }

    void SAction::addButton(int button)
    {
        buttons.push_back(button);
    }

    bool SAction::operator==(const SAction& other) const
    {
        return name == other.name && buttons == other.buttons;
    }

    bool CInputManager::isActionPressed(const SAction& action)
    {
        if (get().m_devices.empty()) return false;
        
        const auto it = std::find(get().m_actions.begin(), get().m_actions.end(), action);
        if (it == get().m_actions.end()) return false;

        for (auto& device : get().m_devices)
        {
            if (it->isDeviceButtonPressed(*device))
                return true;
        }

        return false;
    }

    bool CInputManager::isActionPressed(const std::string& action)
    {
        for (auto& actionObj : get().m_actions)
        {
            if (actionObj.name == action)
            {
                return isActionPressed(actionObj);
            }
        }

        return false;
    }

    SAction& CInputManager::addAction(const SAction& action)
    {
        get().m_actions.emplace_back(action);
        return get().m_actions.back();
    }

    SAction& CInputManager::addAction(std::string name, const std::vector<int>& buttons)
    {
        get().m_actions.emplace_back(std::move(name), buttons);
        return get().m_actions.back();
    }

    CInputManager::CInputManager()
    {
        registerInputDevice<CKeyboardDevice>();
    }

    CInputManager& CInputManager::get()
    {
        static CInputManager instance;
        return instance;
    }
}
