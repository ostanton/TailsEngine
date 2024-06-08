#include <Tails/Input/Action.hpp>

namespace tails
{
    void InputAction::execute(ActionTrigger trigger, InputValue value)
    {
        funcMap[trigger].broadcast(value);
    }
}
