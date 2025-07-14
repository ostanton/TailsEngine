#ifndef TAILS_VECTOR2_HPP
#define TAILS_VECTOR2_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Maths.hpp>

#include <utility>

namespace tails
{
    /**
     * 2-dimensional vector
     * @tparam T Arithmetic type
     */
    template<typename T>
    struct TVector2 final
    {
        constexpr TVector2() = default;
        constexpr TVector2(const T val)
            : x(val), y(val)
        {}
        constexpr TVector2(const T inX, const T inY)
            : x(inX), y(inY)
        {}
        
        template<typename U>
        constexpr explicit TVector2(const TVector2<U>& other)
            : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
        {}
        constexpr TVector2(const TVector2&) = default;

        template<typename U>
        constexpr explicit TVector2(TVector2<U>&& other)
            : x(static_cast<T>(std::move(other.x))), y(static_cast<T>(std::move(other.y)))
        {}
        constexpr TVector2(TVector2&&) noexcept = default;

        template<typename U>
        TVector2& operator=(const TVector2<U>& other)
        {
            x = other.x;
            y = other.y;
            return *this;
        }
        TVector2& operator=(const TVector2&) = default;
        TVector2& operator=(const T val)
        {
            x = val;
            y = val;
            return *this;
        }

        template<typename U>
        TVector2& operator=(TVector2<U>&& other)
        {
            x = static_cast<T>(std::move(other.x));
            y = static_cast<T>(std::move(other.y));
            return *this;
        }
        TVector2& operator=(TVector2&&) noexcept = default;
        
        ~TVector2() = default;

        template<typename U>
        [[nodiscard]] bool operator==(const TVector2<U>& other) const noexcept
        {
            return x == static_cast<T>(other.x)
                && y == static_cast<T>(other.y);
        }
        [[nodiscard]] bool operator==(const TVector2& other) const noexcept {return x == other.x && y == other.y;}
        
        template<typename U>
        [[nodiscard]] bool operator!=(const TVector2<U>& other) const noexcept {return !(*this == other);}
        [[nodiscard]] bool operator!=(const TVector2& other) const noexcept {return !(*this == other);}

        template<typename U>
        [[nodiscard]] TVector2 operator+(const TVector2<U>& other) const noexcept
        {
            return {
                x + static_cast<T>(other.x),
                y + static_cast<T>(other.y)
            };
        }
        
        template<typename U>
        [[nodiscard]] TVector2 operator-(const TVector2<U>& other) const noexcept
        {
            return {
                x - static_cast<T>(other.x),
                y - static_cast<T>(other.y)
            };
        }
        
        template<typename U>
        [[nodiscard]] TVector2 operator*(const TVector2<U>& other) const noexcept
        {
            return {
                x * static_cast<T>(other.x),
                y * static_cast<T>(other.y)
            };
        }
        
        template<typename U>
        [[nodiscard]] TVector2 operator/(const TVector2<U>& other) const noexcept
        {
            return {
                x / static_cast<T>(other.x),
                y / static_cast<T>(other.y)
            };
        }

        template<typename U>
        [[nodiscard]] TVector2 operator+(const U other) const noexcept
        {
            return {x + static_cast<T>(other), y + static_cast<T>(other)};
        }

        template<typename U>
        [[nodiscard]] TVector2 operator-(const U other) const noexcept
        {
            return {x - static_cast<T>(other), y - static_cast<T>(other)};
        }

        template<typename U>
        [[nodiscard]] TVector2 operator*(const U other) const noexcept
        {
            return {x * static_cast<T>(other), y * static_cast<T>(other)};
        }

        template<typename U>
        [[nodiscard]] TVector2 operator/(const U other) const noexcept
        {
            return {x / static_cast<T>(other), y / static_cast<T>(other)};
        }

        TVector2& operator+=(const TVector2& other) noexcept {x += other.x; y += other.y; return *this;}
        TVector2& operator-=(const TVector2& other) noexcept {x -= other.x; y -= other.y; return *this;}
        TVector2& operator*=(const TVector2& other) noexcept {x *= other.x; y *= other.y; return *this;}
        TVector2& operator/=(const TVector2& other) noexcept {x /= other.x; y /= other.y; return *this;}

        template<typename U>
        TVector2& operator+=(const U other) noexcept {x += other; y += other; return *this;}
        template<typename U>
        TVector2& operator-=(const U other) noexcept {x -= other; y -= other; return *this;}
        template<typename U>
        TVector2& operator*=(const U other) noexcept {x *= other; y *= other; return *this;}
        template<typename U>
        TVector2& operator/=(const U other) noexcept {x /= other; y /= other; return *this;}

        [[nodiscard]] TVector2 operator-() const noexcept {return {-x, -y};}

        [[nodiscard]] T distanceSquared(const TVector2 other) const noexcept
        {
            return maths::square(other.x - x) + maths::square(other.y - y);
        }
        
        [[nodiscard]] T distance(const TVector2 other) const noexcept
        {
            return maths::sqrt(distanceSquared(other));
        }

        [[nodiscard]] T length() const noexcept {return maths::sqrt(x * x + y * y);}
        [[nodiscard]] T lengthSquared() const noexcept {return x * x + y * y;}

        bool normalise(const T tolerance) noexcept
        {
            const T squared {lengthSquared()};
            if (squared <= tolerance)
                return false;

            const T scale {maths::fInvSqrt(squared)};
            x *= scale;
            y *= scale;
            return true;
        }

        [[nodiscard]] bool nearlyEqual(const TVector2 other, const T tolerance) const noexcept
        {
            return maths::abs(x - other.x) <= tolerance && maths::abs(y - other.y) <= tolerance;
        }

        [[nodiscard]] bool nearlyZero(const T tolerance) const noexcept
        {
            return maths::abs(x) <= tolerance && maths::abs(y) <= tolerance;
        }

        [[nodiscard]] bool isZero() const noexcept {return x == static_cast<T>(0) && y == static_cast<T>(0);}

        [[nodiscard]] static T distanceSquared(TVector2 a, TVector2 b) noexcept;
        [[nodiscard]] static T distance(TVector2 a, TVector2 b) noexcept;

        static constexpr TVector2 right {1, 0};
        static constexpr TVector2 up {0, 1};
        static constexpr TVector2 identity {0, 0};

        T x {};
        T y {};
    };

    using SVector2f = TVector2<float>;
    using SVector2d = TVector2<double>;
    using SVector2i = TVector2<int>;
    using SVector2u = TVector2<unsigned int>;

    template <typename T>
    T TVector2<T>::distanceSquared(const TVector2 a, const TVector2 b) noexcept
    {
        return a.distanceSquared(b);
    }

    template<typename T>
    T TVector2<T>::distance(const TVector2 a, const TVector2 b) noexcept
    {
        return a.distance(b);
    }
}

#endif // TAILS_VECTOR2_HPP
