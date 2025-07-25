#ifndef TAILS_WORLD_CAMERA_HPP
#define TAILS_WORLD_CAMERA_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Angle.hpp>
#include <Tails/Maths/Matrix3.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/OrientedRect.hpp>
#include <Tails/Maths/Transform2D.hpp>

namespace tails
{
    /**
     * Structure for a camera view (orthographic 2D), typically into a level
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

        [[nodiscard]] SVector2f worldToView(SVector2f worldPoint) const noexcept;
        [[nodiscard]] SFloatRect worldToView(const SFloatRect& worldRect) const noexcept;
        [[nodiscard]] SFloatOrientedRect worldToView(const SFloatOrientedRect& worldRect) const noexcept;
        [[nodiscard]] STransform2D worldToView(const STransform2D& worldTransform) const noexcept;

        [[nodiscard]] SVector2f viewToWorld(SVector2f viewPoint) const noexcept;
        [[nodiscard]] SFloatRect viewToWorld(const SFloatRect& viewRect) const noexcept;
        [[nodiscard]] SFloatOrientedRect viewToWorld(const SFloatOrientedRect& viewRect) const noexcept;
        [[nodiscard]] STransform2D viewToWorld(const STransform2D& viewTransform) const noexcept;
    };
}

#endif // TAILS_WORLD_CAMERA_HPP
