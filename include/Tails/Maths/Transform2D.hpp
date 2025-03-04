#ifndef TAILS_TRANSFORM_2D_HPP
#define TAILS_TRANSFORM_2D_HPP

#include <Tails/Concepts.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Angle.hpp>

namespace tails
{
    template<FloatingPoint T>
    struct TTransform2D final
    {
        TVector2<T> position;
        TAngle<T> rotation;
        TVector2<T> scale {static_cast<T>(1.0)};
    };
}

#endif // TAILS_TRANSFORM_2D_HPP
