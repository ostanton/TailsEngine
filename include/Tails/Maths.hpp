#ifndef TAILS_MATHS_HPP
#define TAILS_MATHS_HPP

#include <concepts>

namespace tails
{
    template<typename T>
    [[nodiscard]] constexpr T lerp(T a, T b, float t) noexcept
    {
        return a + (b - a) * t;
    }

    // TODO - this should be in Tails/Concepts.hpp,
    // but when I move it there, the hash() "in" param can no longer infer its type??? It all breaks!
    template<typename T>
    concept Hashable =
        requires(T str) {{str.size()} -> std::same_as<size_t>;} && (
        requires(T str) {{str[0]} -> std::same_as<char>;} ||
        requires(T str) {{str[0]} -> std::same_as<char&>;} ||
        requires(T str) {{str[0]} -> std::same_as<const char&>;});

    /**
     * Hashes an object into a size_t
     * @param in Must implement size and operator[] which returns a char
     * @return Hashed number
     */
    template<Hashable T>
    [[nodiscard]] constexpr size_t hash(T in) noexcept
    {
        // djb2 algorithm
        size_t result {5381};
        // could change to range-based loop
        // but idk how to check for char in iterator
        for (size_t i {0}; i < in.size(); i++)
        {
            result = (result << 5) + result + in[i];
        }
        return result;
    }
}

#endif // TAILS_MATHS_HPP
