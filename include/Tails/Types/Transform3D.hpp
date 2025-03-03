#ifndef TAILS_TRANSFORM3D_HPP
#define TAILS_TRANSFORM3D_HPP

#include <Tails/Config.hpp>
#include <Tails/Types/Vector3.hpp>

namespace tails
{
    struct TAILS_API STransform3D final
    {
        SVector3f32 position;
        float rotation; // TODO - rotator or quaternion
        SVector3f32 scale;
    };
}

#endif // TAILS_TRANSFORM3D_HPP
