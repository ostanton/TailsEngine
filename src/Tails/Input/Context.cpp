#include <Tails/Input/Context.hpp>

namespace tails
{
    InputContext::InputContext() = default;
    InputContext::~InputContext() = default;

    InputContext::InputContext(const std::unordered_map<std::string, InputAction>& mappings)
        : m_mappings(mappings)
    {
    }

    InputContext::InputContext(const std::pair<std::string, InputAction>& mapping)
    {
        m_mappings[mapping.first] = mapping.second;
    }

    InputContext::InputContext(const std::string& name, const InputAction& action)
    {
        addAction(name, action);
    }

    InputContext::InputContext(const std::string& name, InputAction&& action)
    {
        addAction(name, std::move(action));
    }

    InputContext::InputContext(const InputContext& other)
        : m_mappings(other.m_mappings)
    {
    }

    InputContext::InputContext(InputContext&& other) noexcept
        : m_mappings(std::move(other.m_mappings))
    {
    }

    InputContext& InputContext::operator=(const InputContext& other)
    {
        m_mappings = other.m_mappings;
        
        return *this;
    }

    InputContext& InputContext::operator=(InputContext&& other) noexcept
    {
        m_mappings = std::move(other.m_mappings);

        return *this;
    }

    void InputContext::addAction(const std::string& name, const InputAction& action)
    {
        m_mappings[name] = action;
    }

    void InputContext::addAction(const std::string& name, InputAction&& action)
    {
        m_mappings[name] = std::move(action);
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
