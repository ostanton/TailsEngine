#include <Tails/Input/Context.hpp>

namespace tails
{
    void InputContext::addAction(const std::string& id, InputAction action)
    {
        m_mappings[id] = ActionMapping(action);
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
