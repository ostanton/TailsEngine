#ifndef TAILS_VECTOR2_HPP
#define TAILS_VECTOR2_HPP

#include <Tails/Config.hpp>
#include <Tails/Types/Int.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    /**
     * 2D templated vector with conversions for different typed vectors
     * @tparam T Type for the vector to use
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
        
        T x;
        T y;
    };

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
    TAILS_API using SVector2f = TVector2<float>;
    TAILS_API using SVector2d = TVector2<double>;
}

#endif // TAILS_VECTOR2_HPP
