#pragma once

namespace tails
{
enum class InputActionType
{
    Boolean,
    Float,
    Vector2D
};

/**
 * \brief A simple class to hold the type of the action. This will then be bound to a key
 */
class InputAction
{
public:
    virtual ~InputAction() = default;
    
    InputActionType actionType {InputActionType::Boolean};
    // Can have its own modifiers in the future
};

}
