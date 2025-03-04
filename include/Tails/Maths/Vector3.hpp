#ifndef TAILS_VECTOR3_HPP
#define TAILS_VECTOR3_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    /**
     * Uses Unreal Engine's forward (+X), up (+Z) and right (+Y).
     * So a TVector3 maps to a TVector2 with X, Z being X, Y
     * @tparam T Arithmetic type for the vector
     */
    template<Arithmetic T>
    struct TVector3 final
    {
        TVector3() = default;
        TVector3(T inX, T inY, T inZ)
            : x(inX), y(inY), z(inZ)
        {}
        TVector3(T val)
            : x(val), y(val), z(val)
        {}

        template<Arithmetic U>
        TVector3(const TVector3<U>& other)
            : x(static_cast<T>(other.x))
            , y(static_cast<T>(other.y))
            , z(static_cast<T>(other.z))
        {}
        TVector3(const TVector3&) = default;

        template<typename U>
        TVector3(TVector3<U>&& other) noexcept
            : x(static_cast<T>(std::move(other.x)))
            , y(static_cast<T>(std::move(other.y)))
            , z(static_cast<T>(std::move(other.z)))
        {}
        TVector3(TVector3&&) noexcept = default;

        template<Arithmetic U>
        TVector3& operator=(const TVector3<U>& other)
        {
            x = static_cast<T>(other.X);
            y = static_cast<T>(other.y);
            z = static_cast<T>(other.z);
            return *this;
        }
        TVector3& operator=(const TVector3&) = default;
        
        template<Arithmetic U>
        TVector3& operator=(TVector3<U>&& other) noexcept
        {
            x = static_cast<T>(std::move(other.x));
            y = static_cast<T>(std::move(other.y));
            z = static_cast<T>(std::move(other.z));
            return *this;
        }
        TVector3& operator=(TVector3&&) noexcept = default;
        
        ~TVector3() = default;

        static const TVector3 zero;
        static const TVector3 forward;
        static const TVector3 up;
        static const TVector3 right;
        
        T x;
        T y;
        T z;
    };

    template<Arithmetic T>
    const TVector3<T> TVector3<T>::zero(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
    template<Arithmetic T>
    const TVector3<T> TVector3<T>::forward(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
    template<Arithmetic T>
    const TVector3<T> TVector3<T>::up(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
    template<Arithmetic T>
    const TVector3<T> TVector3<T>::right(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

    TAILS_API using SVector3u8 = TVector3<u8>;
    TAILS_API using SVector3u16 = TVector3<u16>;
    TAILS_API using SVector3u32 = TVector3<u32>;
    TAILS_API using SVector3u64 = TVector3<u64>;

    TAILS_API using SVector3i8 = TVector3<i8>;
    TAILS_API using SVector3i16 = TVector3<i16>;
    TAILS_API using SVector3i32 = TVector3<i32>;
    TAILS_API using SVector3i64 = TVector3<i64>;

    TAILS_API using SVector3f32 = TVector3<f32>;
    TAILS_API using SVector3f64 = TVector3<f64>;

    TAILS_API using SVector3u = TVector3<unsigned int>;
    TAILS_API using SVector3i = TVector3<int>;
    TAILS_API using SVector3f = SVector3f32;
    TAILS_API using SVector3d = SVector3f64;
}

#endif // TAILS_VECTOR3_HPP
