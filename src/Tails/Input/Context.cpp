#include <Tails/Input/Context.hpp>

namespace tails
{
    void InputContext::addAction(const std::string& name, const InputAction& action)
    {
        m_mappings[name] = action;
    }

    InputAction& InputContext::getAction(const std::string& name)
    {
        return m_mappings[name];
    }

    void InputContext::removeAction(const std::string& name)
    {
        m_mappings.erase(name);
    }

    void InputContext::tick(float deltaTime)
    {
        for (auto& [key, value] : m_mappings)
        {
            value.tick(deltaTime);
        }
    }
}
