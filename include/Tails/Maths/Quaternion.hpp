#ifndef TAILS_QUATERNION_HPP
#define TAILS_QUATERNION_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>

namespace tails
{
    template<FloatingPoint T>
    struct TQuaternion final
    {
        T x;
        T y;
        T z;
        T w;

        // TODO - from euler stuff
    };

    TAILS_API using SQuaternionf32 = TQuaternion<f32>;
    TAILS_API using SQuaternionf64 = TQuaternion<f64>;

    TAILS_API using SQuaternionf = SQuaternionf32;
    TAILS_API using SQuaterniond = SQuaternionf64;
}

#endif // TAILS_QUATERNION_HPP
