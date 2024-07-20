#include <Tails/Input/Action.hpp>

namespace tails
{
    InputAction::InputAction(const std::vector<Key>& keys,
                             const std::unordered_map<ActionTrigger, MultiEvent<>>& events)
        : m_events(events), m_keys(keys)
    {

    }

    InputAction::InputAction(const Key& key, const std::pair<ActionTrigger, MultiEvent<>>& event)
    {
        m_keys.push_back(key);
        m_events[event.first] = event.second;
    }

    InputAction::InputAction(const std::vector<Key>& keys, const std::pair<ActionTrigger, MultiEvent<>>& event)
        : m_keys(keys)
    {
        m_events[event.first] = event.second;
    }

    bool InputAction::containsKey(const Key& key) const
    {
        if (auto it = std::find(m_keys.begin(), m_keys.end(), key); it != m_keys.end())
        {
            return true;
        }

        return false;
    }

    void InputAction::tick(float deltaTime)
    {
        if (anyKeyPressed())
        {
            currentState = true;

            if (currentState != lastState)
            {
                lastState = currentState;
                broadcastTrigger(ActionTrigger::Started);
            }

            broadcastTrigger(ActionTrigger::Triggered);
        }
        else
        {
            currentState = false;

            if (currentState != lastState)
            {
                lastState = currentState;
                broadcastTrigger(ActionTrigger::Completed);
            }
        }
    }

    bool InputAction::anyKeyPressed() const
    {
        for (auto& key : m_keys)
        {
            if (key.isPressed())
                return true;
        }

        return false;
    }

    void InputAction::broadcastTrigger(ActionTrigger trigger)
    {
        if (m_events.contains(trigger))
            m_events[trigger].broadcast();
    }
}
