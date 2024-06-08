#ifndef TAILS_INPUTACTION_HPP
#define TAILS_INPUTACTION_HPP

#include <Tails/Events/MultiEvent.hpp>
#include <Tails/Input/Value.hpp>

#include <string>
#include <unordered_map>
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
        std::unordered_map<ActionTrigger, MultiEvent<InputValue>> funcMap;

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(InputValue))
        {
            funcMap[trigger].add(object, function);
        }

        void execute(ActionTrigger trigger, InputValue value);
    };
}

#endif // TAILS_INPUTACTION_HPP
