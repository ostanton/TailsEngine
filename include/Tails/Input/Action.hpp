#ifndef TAILS_INPUTACTION_HPP
#define TAILS_INPUTACTION_HPP

#include <Tails/Config.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Events/MultiEvent.hpp>
#include <Tails/Input/Keys.hpp>

#include <string>
#include <unordered_map>
#include <memory>

namespace tails
{
    class InputContext;

    enum class TAILS_API ActionTrigger
    {
        Started,
        Triggered,
        Completed
    };

    struct TAILS_API InputAction final : public Tickable
    {
        friend InputContext;

        InputAction() = default;
        InputAction(const std::vector<Key>& keys, const std::unordered_map<ActionTrigger, MultiEvent<>>& events);
        InputAction(const Key& key, const std::pair<ActionTrigger, MultiEvent<>>& event);
        InputAction(const std::vector<Key>& keys, const std::pair<ActionTrigger, MultiEvent<>>& event);

        [[nodiscard]] MultiEvent<>& getEvent(ActionTrigger trigger) {return m_events[trigger];}
        [[nodiscard]] const std::unordered_map<ActionTrigger, MultiEvent<>>& getEvents() const {return m_events;}

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)())
        {
            m_events[trigger].add(object, function);
        }

        void addKey(const Key& key) {m_keys.push_back(key);}
        [[nodiscard]] bool containsKey(const Key& key) const;
        [[nodiscard]] const std::vector<Key>& getKeys() const {return m_keys;}

    private:
        void tick(float deltaTime) override;

        [[nodiscard]] bool anyKeyPressed() const;
        void broadcastTrigger(ActionTrigger trigger);

        std::unordered_map<ActionTrigger, MultiEvent<>> m_events;
        std::vector<Key> m_keys;
        bool lastState {false};
        bool currentState {false};
    };
}

#endif // TAILS_INPUTACTION_HPP
