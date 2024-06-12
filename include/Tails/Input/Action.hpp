#ifndef TAILS_INPUTACTION_HPP
#define TAILS_INPUTACTION_HPP

#include <Tails/Config.hpp>
#include <Tails/Events/MultiEvent.hpp>
#include <Tails/Input/Value.hpp>

#include <string>
#include <unordered_map>
#include <memory>

namespace tails
{
    enum class TAILS_API ActionTrigger
    {
        Started,
        Triggered,
        Completed
    };

    struct TAILS_API InputAction final
    {
        InputAction() = default;

        std::string name;
        std::unordered_map<ActionTrigger, MultiEvent<InputValue>> funcMap;

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(InputValue&&))
        {
            funcMap[trigger].add(object, function);
        }

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(const InputValue&))
        {
            funcMap[trigger].add(object, function);
        }

        void execute(ActionTrigger trigger, InputValue value);
    };
}

#endif // TAILS_INPUTACTION_HPP
