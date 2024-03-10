#pragma once

namespace tails
{
/**
 * \brief A class that "modifies" the input in some way, albeit it blocking the input from happening under
 * certain circumstances, altering the output of the input, etc.
 */
class InputActionModifier
{
public:
    virtual ~InputActionModifier() = default;
};

}
