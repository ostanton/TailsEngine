#ifndef TAILS_MATHS_HPP
#define TAILS_MATHS_HPP

namespace tails
{
    template<typename T>
    [[nodiscard]] constexpr T lerp(T a, T b, float t) noexcept
    {
        return a + (b - a) * t;
    }
}

#endif // TAILS_MATHS_HPP
