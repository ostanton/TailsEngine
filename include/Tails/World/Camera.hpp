#ifndef TAILS_WORLD_CAMERA_HPP
#define TAILS_WORLD_CAMERA_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    struct TAILS_API SCamera
    {
        SVector2f position {0.f};
        /** In radians */
        double rotation {0};
        float zoom {1.f};

        void rotate(float degrees) noexcept;
        [[nodiscard]] float getRotationDegrees() const noexcept;
    };
}

#endif // TAILS_WORLD_CAMERA_HPP
