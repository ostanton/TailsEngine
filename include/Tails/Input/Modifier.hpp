#ifndef TAILS_INPUTMODIFIER_HPP
#define TAILS_INPUTMODIFIER_HPP

#include <Tails/Config.hpp>
#include <Tails/Input/Value.hpp>

namespace tails
{
    // class that modifies an input value
    class TAILS_API InputModifier
    {
    protected:
        virtual InputValue tick(float deltaTime, InputValue currentValue) = 0;
    };
}

#endif // TAILS_INPUTMODIFIER_HPP
