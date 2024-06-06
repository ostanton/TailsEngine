#ifndef TAILS_INPUTVALUE_HPP
#define TAILS_INPUTVALUE_HPP

#include <variant>

namespace tails
{
    struct InputValue final
    {
        std::variant<bool, float> value;

        template<typename T>
        T getValue()
        {
            return std::get<T>(value);
        }

        template<typename T>
        T isValueType()
        {
            return std::holds_alternative<T>(value);
        }
    };
}

#endif // TAILS_INPUTVALUE_HPP
