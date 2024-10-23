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

    /**
     * Hashes an object into a size_t
     * @param str Must implement begin and end functions with char
     * @return Hashed number
     */
    template<typename T>
    // TODO - make these requirements nicer
    requires
    requires (T str) {{str.size()} -> std::same_as<size_t>;} &&
    requires (T str)
    {
        {str[0]} -> std::same_as<const char&>;
    } ||
    requires (T str)
    {
        {str[0]} -> std::same_as<char>;
    } ||
    requires (T str)
    {
        {str[0]} -> std::same_as<char&>;
    }
    [[nodiscard]] constexpr size_t hash(T str) noexcept
    {
        // djb2 algorithm
        size_t result {5381};
        // could change to range-based loop
        // but idk how to check for char in iterator
        for (size_t i {0}; i < str.size(); i++)
        {
            result = (result << 5) + result + str[i];
        }
        return result;
    }
}

#endif // TAILS_MATHS_HPP
