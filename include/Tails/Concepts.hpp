#ifndef TAILS_CONCEPTS_HPP
#define TAILS_CONCEPTS_HPP

#include <type_traits>
#include <ostream>
#include <filesystem>

namespace tails
{
    template<typename T>
    concept UserType = std::is_class_v<T>;
    
    template<typename T, typename... Ts>
    concept ConstructibleUserType =
        UserType<T> &&
        std::constructible_from<T, Ts...>;

    /**
     * Checks if a type can be printed via streams
     */
    template<typename T>
    concept PrintableStream = requires(T obj, std::ostream& os)
    {
        {os << obj} -> std::same_as<std::ostream&>;
    };

    template<typename... Ts>
    concept PrintableStreamAll = (PrintableStream<Ts> && ...);

    /**
     * Wrapper for std::derived_from
     */
    template<typename Derived, typename Base>
    concept Derives = std::derived_from<Derived, Base>;

    /**
     * To be a resource type, it must have a constructor that takes a const-ref filesystem::path,
     * and must be movable
     */
    template<typename T>
    concept ResourceType =
        std::constructible_from<T, const std::filesystem::path&> &&
        std::movable<T>;

    template<typename T>
    concept FloatingPoint = std::floating_point<T>;

    template<typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template<typename T>
    concept Hashable =
        requires(T str) {{str.size()} -> std::same_as<size_t>;} && (
        requires(T str) {{str[0]} -> std::same_as<char>;} ||
        requires(T str) {{str[0]} -> std::same_as<char&>;} ||
        requires(T str) {{str[0]} -> std::same_as<const char&>;});
}

#endif // TAILS_CONCEPTS_HPP
