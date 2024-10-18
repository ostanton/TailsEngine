#ifndef TAILS_MATHS_H
#define TAILS_MATHS_H

namespace tails
{
    template<typename T>
    [[nodiscard]] constexpr T lerp(T a, T b, float t) noexcept
    {
        return a + (b - a) * t;
    }
}

#endif // TAILS_MATHS_H
