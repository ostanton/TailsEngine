#include <Tails/Input/Context.hpp>

namespace tails
{
    InputContext::InputContext(InputContext&& other) noexcept
    {
        m_mappings = std::move(other.m_mappings);
    }

    void InputContext::addAction(const std::string& id, InputAction action)
    {
        m_mappings[id] = ActionMapping(std::move(action));
    }

    ActionMapping& InputContext::getActionMapping(const std::string& id)
    {
        return m_mappings[id];
    }

    std::unordered_map<std::string, ActionMapping>& InputContext::getMappings()
    {
        return m_mappings;
    }
}
