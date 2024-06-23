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
        std::unordered_map<ActionTrigger, MultiEvent<bool>> funcMap;
        bool currentValue {false}; // value this frame
        bool lastValue {false}; // value last frame

        template<typename C>
        void addFunction(ActionTrigger trigger, C* object, void(C::*function)(bool))
        {
            if (funcMap.contains(trigger))
                funcMap[trigger].add(object, function);

            MultiEvent<bool> event;
            event.add(object, function);
            funcMap[trigger] = MultiEvent<bool>(std::move(event));
        }

        void execute(ActionTrigger trigger);
        void execute(ActionTrigger trigger, bool value);
    };
}

#endif // TAILS_INPUTACTION_HPP
