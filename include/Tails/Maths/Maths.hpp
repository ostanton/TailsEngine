#ifndef TAILS_MATHS_HPP
#define TAILS_MATHS_HPP

#include <cmath>

namespace tails::maths
{
    template<typename T> [[nodiscard]] constexpr T square(T x) noexcept {return x * x;}
    template<typename T> [[nodiscard]] constexpr T cube(T x) noexcept {return x * x * x;}
    template<typename T> [[nodiscard]] constexpr T sqrt(T x) noexcept {return std::sqrt(x);}
    template<typename T> [[nodiscard]] constexpr T invSqrt(T x) noexcept {return static_cast<T>(1) / sqrt(x);}
    template<typename T> [[nodiscard]] constexpr T fInvSqrt(T x) noexcept
    {
        // id-tech fast inverse sqrt
        // I don't understand it, but it works :D
        const float x2 = x * 0.5f;
        constexpr float threeHalves {1.5f};
        float y = x;
        long i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (threeHalves - x2 * y * y);
        return y;
    }
    template<typename T> [[nodiscard]] constexpr T abs(T x) noexcept {return x > static_cast<T>(0) ? x : -x;}
    template<typename T> [[nodiscard]] constexpr T max(T a, T b) noexcept {return a > b ? a : b;}
    template<typename T> [[nodiscard]] constexpr T min(T a, T b) noexcept {return a < b ? a : b;}
    template<typename T, typename U> [[nodiscard]] constexpr T power(T x, U exp) noexcept {return std::pow(x, exp);}
}

#endif // TAILS_MATHS_HPP
