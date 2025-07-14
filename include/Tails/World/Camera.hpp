#ifndef TAILS_WORLD_CAMERA_HPP
#define TAILS_WORLD_CAMERA_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Angle.hpp>
#include <Tails/Maths/Matrix3.hpp>

namespace tails
{
    template<typename>
    struct TTransform2D;

    /**
     * Structure for a camera view, typically into a level
     */
    struct TAILS_API SCamera
    {
        SVector2f position {0.f};
        /** In radians */
        SFloatAngle rotation;
        float height {1000.f};
        float zoom {1.f};

        void rotate(SFloatAngle angle) noexcept;

        [[nodiscard]] SMatrix3f getViewMatrix() const noexcept;
        [[nodiscard]] SMatrix3f getProjectionMatrix() const noexcept;

        [[nodiscard]] SVector2f worldToView(SVector2f point) const noexcept;
        [[nodiscard]] TTransform2D<float> worldToView(const TTransform2D<float>& transform) const noexcept;
    };
}

#endif // TAILS_WORLD_CAMERA_HPP
