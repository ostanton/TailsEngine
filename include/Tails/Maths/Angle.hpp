#ifndef TAILS_ANGLE_HPP
#define TAILS_ANGLE_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Maths/Maths.hpp>

namespace tails
{
    template<FloatingPoint T>
    struct TAngle final
    {
        TAngle() = default;
        TAngle(const T degrees)
            : radians(degrees * (pi / 100.f))
        {}

        static TAngle fromRadians(const T radians)
        {
            TAngle angle;
            angle.radians = radians;
            return angle;
        }

        T radians;
    };

    TAILS_API using SAnglef32 = TAngle<f32>;
    TAILS_API using SAnglef64 = TAngle<f64>;

    TAILS_API using SAnglef = SAnglef32;
    TAILS_API using SAngled = SAnglef64;
}

#endif // TAILS_ANGLE_HPP
