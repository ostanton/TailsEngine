#ifndef TAILS_VERTEX_HPP
#define TAILS_VERTEX_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/FloatColour.hpp>

namespace tails
{
    /**
     * A simple 2D vertex
     */
    struct TAILS_API SVertex final
    {
        SVector2f position;
        SFloatColour colour;
        SVector2f texCoord;
    };
}

#endif // TAILS_VERTEX_HPP
