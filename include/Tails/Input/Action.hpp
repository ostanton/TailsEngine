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
        InputValue currentValue; // value this frame
        InputValue lastValue; // value last frame

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(InputValue))
        {
            if (funcMap.contains(trigger))
                funcMap[trigger].add(object, function);

            MultiEvent<InputValue> event;
            event.add(object, function);
            funcMap.try_emplace(trigger, MultiEvent<InputValue>(event));
        }

        void execute(ActionTrigger trigger);
    };
}

#endif // TAILS_INPUTACTION_HPP
