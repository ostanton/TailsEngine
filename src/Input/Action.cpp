#include <Tails/Input/Action.hpp>

namespace tails
{
    void InputAction::execute(ActionTrigger trigger)
    {
        funcMap[trigger].broadcast(currentValue);
    }
}
