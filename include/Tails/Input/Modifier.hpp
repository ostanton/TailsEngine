#ifndef TAILS_INPUTMODIFIER_HPP
#define TAILS_INPUTMODIFIER_HPP

#include <Tails/Input/Value.hpp>

namespace tails
{
    // class that modifies an input value
    class InputModifier
    {
    protected:
        virtual InputValue tick(float deltaTime, InputValue currentValue) = 0;
    };
}

#endif // TAILS_INPUTMODIFIER_HPP
