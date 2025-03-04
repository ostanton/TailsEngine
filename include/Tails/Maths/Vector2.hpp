#ifndef TAILS_VECTOR2_HPP
#define TAILS_VECTOR2_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    /**
     * 2D templated vector with conversions for different typed vectors
     * @tparam T Arithmetic type for the vector
     */
    template<Arithmetic T>
    struct TVector2 final
    {
        TVector2() = default;
        TVector2(T inX, T inY)
            : x(inX), y(inY)
        {}
        TVector2(T val)
            : x(val), y(val)
        {}
        
        template<Arithmetic U>
        TVector2(const TVector2<U>& other)
            : x(static_cast<T>(other.x)), y(static_cast<T>(other.y))
        {}
        TVector2(const TVector2&) = default;

        template<Arithmetic U>
        TVector2(TVector2<U>&& other) noexcept
            : x(static_cast<T>(std::move(other.x))), y(static_cast<T>(std::move(other.y)))
        {}
        TVector2(TVector2&&) noexcept = default;
        
        template<Arithmetic U>
        TVector2& operator=(const TVector2<U>& other)
        {
            x = static_cast<T>(other.X);
            y = static_cast<T>(other.y);
            return *this;
        }
        TVector2& operator=(const TVector2&) = default;
        
        template<Arithmetic U>
        TVector2& operator=(TVector2<U>&& other) noexcept
        {
            x = static_cast<T>(std::move(other.x));
            y = static_cast<T>(std::move(other.y));
            return *this;
        }
        TVector2& operator=(TVector2&&) noexcept = default;
        
        ~TVector2() = default;

        [[nodiscard]] TVector2 operator+(const TVector2& other) const {return {x + other.x, y + other.y};}
        [[nodiscard]] TVector2 operator+(T factor) const {return {x + factor, y + factor};}
        [[nodiscard]] TVector2 operator-(const TVector2& other) const {return {x - other.x, y - other.y};}
        [[nodiscard]] TVector2 operator-(T factor) const {return {x - factor, y - factor};}
        [[nodiscard]] TVector2 operator*(const TVector2& other) const {return {x * other.x, y * other.y};}
        [[nodiscard]] TVector2 operator*(T factor) const {return {x * factor, y * factor};}
        [[nodiscard]] TVector2 operator/(const TVector2& other) const {return {x / other.x, y / other.y};}
        [[nodiscard]] TVector2 operator/(T factor) const {return {x / factor, y / factor};}

        [[nodiscard]] bool operator==(const TVector2&) const = default;
        [[nodiscard]] bool operator!=(const TVector2&) const = default;

        [[nodiscard]] TVector2 operator-() const {return {-x, -y};}

        [[nodiscard]] TVector2 operator+=(const TVector2& other)
        {
            x += other.x;
            y += other.y;
            return *this;
        }
        [[nodiscard]] TVector2 operator-=(const TVector2& other)
        {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        [[nodiscard]] TVector2 operator*=(const TVector2& other)
        {
            x *= other.x;
            y *= other.y;
            return *this;
        }
        [[nodiscard]] TVector2 operator*=(T factor)
        {
            x *= factor;
            y *= factor;
            return *this;
        }
        [[nodiscard]] TVector2 operator/=(const TVector2& other)
        {
            x /= other.x;
            y /= other.y;
            return *this;
        }
        [[nodiscard]] TVector2 operator/=(T factor)
        {
            x /= factor;
            y /= factor;
            return *this;
        }

        void normalise(T tolerance)
        {
            const T square {x * x + y * y};
            if (square > tolerance)
            {
                const T scale {}; // TODO - inverse square root
                x *= scale;
                y *= scale;
                return;
            }

            x = static_cast<T>(0);
            y = static_cast<T>(0);
        }

        [[nodiscard]] bool isNearlyZero(T tolerance) const
        {
            return std::abs(x) <= tolerance
                && std::abs(y) <= tolerance;
        }

        [[nodiscard]] bool isZero() const
        {
            return x == static_cast<T>(0)
                && y == static_cast<T>(0);
        }

        [[nodiscard]] T length() const
        {
            return std::sqrt(x * x + y * y);
        }

        [[nodiscard]] T lengthSquared() const
        {
            return x * x + y * y;
        }

        [[nodiscard]] T dot(const TVector2& other) const
        {
            return x * other.x + y * other.y;
        }

        static const TVector2 zero;
        static const TVector2 up;
        static const TVector2 right;
        
        T x;
        T y;
    };

    template<Arithmetic T>
    const TVector2<T> TVector2<T>::zero(static_cast<T>(0), static_cast<T>(0));
    template<Arithmetic T>
    const TVector2<T> TVector2<T>::up(static_cast<T>(0), static_cast<T>(1));
    template<Arithmetic T>
    const TVector2<T> TVector2<T>::right(static_cast<T>(1), static_cast<T>(0));

    TAILS_API using SVector2u8 = TVector2<u8>;
    TAILS_API using SVector2u16 = TVector2<u16>;
    TAILS_API using SVector2u32 = TVector2<u32>;
    TAILS_API using SVector2u64 = TVector2<u64>;

    TAILS_API using SVector2i8 = TVector2<i8>;
    TAILS_API using SVector2i16 = TVector2<i16>;
    TAILS_API using SVector2i32 = TVector2<i32>;
    TAILS_API using SVector2i64 = TVector2<i64>;

    TAILS_API using SVector2f32 = TVector2<f32>;
    TAILS_API using SVector2f64 = TVector2<f64>;

    TAILS_API using SVector2u = TVector2<unsigned int>;
    TAILS_API using SVector2i = TVector2<int>;
    TAILS_API using SVector2f = SVector2f32;
    TAILS_API using SVector2d = SVector2f64;
}

#endif // TAILS_VECTOR2_HPP
