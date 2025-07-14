#include <Tails/World/Camera.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Maths/Vector3.hpp>

namespace tails
{
    void SCamera::rotate(const SFloatAngle angle) noexcept
    {
        rotation += angle;
    }

    SMatrix3f SCamera::getViewMatrix() const noexcept
    {
        const float radians {rotation.asRadians()};
        const float cosA {std::cos(-radians)};
        const float sinA {std::sin(-radians)};

        const SMatrix3f rotationMatrix {
            cosA, -sinA, 0.f,
            sinA, cosA, 0.f,
            0.f, 0.f, 1.f
        };

        const SMatrix3f translationMatrix {
            1.f, 0.f, -position.x,
            0.f, 1.f, -position.y,
            0.f, 0.f, 1.f
        };

        return rotationMatrix * translationMatrix;
    }

    SMatrix3f SCamera::getProjectionMatrix() const noexcept
    {
        const float half {height * 0.5f / zoom};

        float left {-half};
        float right {half};
        float bottom {-half};
        float top {half};

        const float rl {right - left};
        const float tb {top - bottom};
        return {
            2.f / rl, 0.f, -(right + left) / rl,
            0.f, 2.f / tb, -(top + bottom) / tb,
            0.f, 0.f, 1.f
        };
    }

    SVector2f SCamera::worldToView(const SVector2f point) const noexcept
    {
        const SMatrix3f worldToNDC {getProjectionMatrix() * getViewMatrix()};
        const SVector3f ndc {worldToNDC * SVector3f {point.x, point.y, 1.f}};

        const SVector2f windowSize {render::getResolution()};
        return {
            (ndc.x + 1.f) * 0.5f * windowSize.x,
            (1.f - (ndc.y + 1.f) * 0.5f) * windowSize.y
        };
    }

    TTransform2D<float> SCamera::worldToView(const TTransform2D<float>& transform) const noexcept
    {
        const SVector2f windowSize {render::getResolution()};

        const SMatrix3f ndcToScreenMatric {
            windowSize.x / 2.f, 0.f, windowSize.x / 2.f,
            0.f, -windowSize.y / 2.f, windowSize.y / 2.f,
            0.f, 0.f, 1.f
        };
        const auto screenMatrix = getProjectionMatrix() * getViewMatrix() * transform.getMatrix();

        return {ndcToScreenMatric * screenMatrix};
    }
}
