#include <Tails/Input/Context.hpp>

namespace tails
{
    InputValue MappingData::getModifiedValue(float deltaTime) const
    {
        InputValue currentValue;
        for (auto& modifier : modifiers)
        {
            currentValue = modifier->modify(deltaTime, currentValue);
        }

        return currentValue;
    }

    InputContext::InputContext(InputContext&& other) noexcept
    {
        m_mappings = std::move(other.m_mappings);
    }

    InputContext& InputContext::operator=(InputContext&& other) noexcept
    {
        m_mappings = std::move(other.m_mappings);
        return *this;
    }

    void InputContext::addAction(const std::string& id, InputAction action)
    {
        m_mappings[id] = ActionMapping(std::move(action));
    }

    void InputContext::addActionMapping(const std::string& id, ActionMapping& mapping)
    {
        m_mappings[id] = std::move(mapping);
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
