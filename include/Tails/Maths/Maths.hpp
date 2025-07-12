#ifndef TAILS_MATHS_HPP
#define TAILS_MATHS_HPP

#include <cmath>
#include <numbers>

namespace tails::maths
{
    template<typename T> constexpr T pi {std::numbers::pi_v<T>};
    template<typename T> [[nodiscard]] constexpr T square(const T x) noexcept {return x * x;}
    template<typename T> [[nodiscard]] constexpr T cube(const T x) noexcept {return x * x * x;}
    template<typename T> [[nodiscard]] constexpr T sqrt(const T x) noexcept {return std::sqrt(x);}
    template<typename T> [[nodiscard]] constexpr T invSqrt(const T x) noexcept {return static_cast<T>(1) / sqrt(x);}
    template<typename T> [[nodiscard]] constexpr T fInvSqrt(const T x) noexcept
    {
        // id-tech fast inverse sqrt
        // I don't understand it, but I think it works :/ (:D)
        const float x2 = x * 0.5f;
        constexpr float threeHalves {1.5f};
        float y = x;
        long i = *(long*)&y;
        i = 0x5f3759df - (i >> 1);
        y = *(float*)&i;
        y = y * (threeHalves - x2 * y * y);
        return y;
    }
    template<typename T> [[nodiscard]] constexpr T abs(const T x) noexcept {return x > static_cast<T>(0) ? x : -x;}
    template<typename T> [[nodiscard]] constexpr T max(const T a, const T b) noexcept {return a > b ? a : b;}
    template<typename T> [[nodiscard]] constexpr T min(const T a, const T b) noexcept {return a < b ? a : b;}
    template<typename T, typename U> [[nodiscard]] constexpr T power(const T x, const U exp) noexcept {return std::pow(x, exp);}
    template<typename T>
    [[nodiscard]] constexpr bool nearlyEqual(const T a, const T b, const T tolerance) noexcept
    {
        const T absA {abs(a)};
        const T absB {abs(b)};
        return abs(a - b) <= (absA < absB ? absB : absA) * tolerance;
    }
    template<typename T> [[nodiscard]] constexpr T degToRad(T degrees) noexcept
    {
        return degrees * pi<T> / static_cast<T>(180);
    }
    template<typename T> [[nodiscard]] constexpr T radToDeg(T radians) noexcept
    {
        return radians * static_cast<T>(180) / pi<T>;
    }
}

#endif // TAILS_MATHS_HPP
