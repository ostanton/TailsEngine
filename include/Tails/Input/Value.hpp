#ifndef TAILS_INPUTVALUE_HPP
#define TAILS_INPUTVALUE_HPP

#include <Tails/Config.hpp>

#include <variant>

namespace tails
{
    struct TAILS_API InputValue final
    {
        std::variant<bool, float> value;

        template<typename T>
        T getValue() const
        {
            return std::get<T>(value);
        }

        template<typename T>
        T isValueType() const
        {
            return std::holds_alternative<T>(value);
        }
    };
}

#endif // TAILS_INPUTVALUE_HPP
