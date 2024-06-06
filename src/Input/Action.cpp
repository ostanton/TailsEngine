#include <Tails/Input/Action.hpp>

namespace tails
{
    void InputAction::execute(ActionTrigger trigger, InputValue value)
    {
        for (auto& event : funcMap[trigger])
        {
            event.execute(value);
        }
    }
}
