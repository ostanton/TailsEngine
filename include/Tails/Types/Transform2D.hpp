#ifndef TAILS_TRANSFORM2D_HPP
#define TAILS_TRANSFORM2D_HPP

#include <Tails/Config.hpp>
#include <Tails/Types/Vector2.hpp>

namespace tails
{
    struct TAILS_API STransform2D final
    {
        SVector2f32 position;
        float angle;
        SVector2f32 scale;
    };
}

#endif // TAILS_TRANSFORM2D_HPP
