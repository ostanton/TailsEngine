#ifndef TAILS_MATHS_HPP
#define TAILS_MATHS_HPP

#include <Tails/Concepts.hpp>

namespace tails
{
    template<Arithmetic T>
    constexpr T pi {static_cast<T>(3.141592653589793)};
    
    template<typename T>
    [[nodiscard]] constexpr T lerp(T a, T b, float t) noexcept
    {
        return a + (b - a) * t;
    }

    /**
     * Hashes an object into a size_t
     * @param in Must implement size and operator[] which returns a char
     * @return Hashed number
     */
    template<Hashable T>
    [[nodiscard]] constexpr size_t hash(const T& in) noexcept
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
