#include <Tails/Input/Action.hpp>

namespace tails
{
    void InputAction::execute(ActionTrigger trigger)
    {
        funcMap[trigger].broadcast(currentValue);
    }

    void InputAction::execute(ActionTrigger trigger, bool value)
    {
        lastValue = currentValue;
        currentValue = value;
        execute(trigger);
    }
}
