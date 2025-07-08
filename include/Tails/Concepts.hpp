#ifndef TAILS_CONCEPTS_HPP
#define TAILS_CONCEPTS_HPP

#include <concepts>
#include <utility>
#include <type_traits>

namespace tails
{
    template<typename DerivedT, typename BaseT>
    concept DerivedFrom = std::derived_from<DerivedT, BaseT>;

    template<typename T, typename... ArgsT>
    concept ConstructibleFrom = std::constructible_from<T, ArgsT...>;

    template<typename T>
    concept Destructible = std::is_destructible_v<T>;

    template<typename T>
    concept Enum = std::is_enum_v<T>;

    template<typename T, typename RetT, typename... ArgsT>
    concept Invocable = std::invocable<T, ArgsT...> && requires(T func, ArgsT&&... args)
    {
        {func(std::forward<ArgsT>(args)...)} -> std::same_as<RetT>;
    };

    template<typename T, typename... ArgsT>
    concept Predicate = std::predicate<T, ArgsT...>;

    template<typename T>
    concept UserType = std::is_class_v<T>;

    template<typename T>
    concept Integral = std::integral<T>;
}

#endif // TAILS_CONCEPTS_HPP
