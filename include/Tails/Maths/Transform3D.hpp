#ifndef TAILS_TRANSFORM_3D_HPP
#define TAILS_TRANSFORM_3D_HPP

#include <Tails/Concepts.hpp>
#include <Tails/Maths/Vector3.hpp>
#include <Tails/Maths/Quaternion.hpp>

namespace tails
{
    template<FloatingPoint T>
    struct TTransform3D final
    {
        TVector3<T> position;
        TQuaternion<T> rotation;
        TVector3<T> scale {static_cast<T>(1.0)};
    };
}

#endif // TAILS_TRANSFORM_3D_HPP
