#ifndef TAILS_INPUTACTION_HPP
#define TAILS_INPUTACTION_HPP

#include <Tails/Input/Value.hpp>
#include <Tails/Events/Event.hpp>

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace tails
{
    enum class ActionTrigger
    {
        Started,
        Triggered,
        Completed
    };

    struct InputAction final
    {
        InputAction() = default;

        std::string name;
        std::unordered_map<ActionTrigger, std::vector<Event<InputValue>>> funcMap;

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(InputValue))
        {
            Event<InputValue> event;
            event.bind(object, function);
            funcMap[trigger].push_back(std::move(event));
        }

        void execute(ActionTrigger trigger, InputValue value);
    };
}

#endif // TAILS_INPUTACTION_HPP
