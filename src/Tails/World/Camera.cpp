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
        const SVector2f windowSize {render::getResolution()};
        const float windowAspect {windowSize.x / windowSize.y};
        const float halfHeight {height * 0.5f / zoom};
        const float halfWidth {halfHeight * windowAspect};

        float left {-halfWidth};
        float right {halfWidth};
        float bottom {-halfHeight};
        float top {halfHeight};

        const float rl {right - left};
        const float tb {top - bottom};
        return {
            2.f / rl, 0.f, -(right + left) / rl,
            0.f, 2.f / tb, -(top + bottom) / tb,
            0.f, 0.f, 1.f
        };
    }

    SVector2f SCamera::worldToView(const SVector2f worldPoint) const noexcept
    {
        const SMatrix3f worldToNDC {getProjectionMatrix() * getViewMatrix()};
        const SVector3f ndc {worldToNDC * SVector3f {worldPoint.x, worldPoint.y, 1.f}};

        const SVector2f windowSize {render::getResolution()};
        return {
            (ndc.x + 1.f) * 0.5f * windowSize.x,
            (1.f - (ndc.y + 1.f) * 0.5f) * windowSize.y
        };
    }

    TTransform2D<float> SCamera::worldToView(const TTransform2D<float>& worldTransform) const noexcept
    {
        const SVector2f windowSize {render::getResolution()};

        const SMatrix3f ndcToScreenMatric {
            windowSize.x / 2.f, 0.f, windowSize.x / 2.f,
            0.f, -windowSize.y / 2.f, windowSize.y / 2.f,
            0.f, 0.f, 1.f
        };
        const auto screenMatrix = getProjectionMatrix() * getViewMatrix() * worldTransform.getMatrix();

        return {ndcToScreenMatric * screenMatrix};
    }

    SVector2f SCamera::viewToWorld(const SVector2f viewPoint) const noexcept
    {
        const SVector2f windowSize {render::getResolution()};
        const SVector2f ndc {
            viewPoint.x / windowSize.x * 2.f - 1.f,
            -(viewPoint.y / windowSize.y * 2.f - 1.f)
        };

        const SVector3f ndcPoint {ndc.x, ndc.y, 1.f};
        const SMatrix3f invWorldToNDC {(getProjectionMatrix() * getViewMatrix()).inverse()};
        const SVector3f worldPoint {invWorldToNDC * ndcPoint};
        return {worldPoint.x, worldPoint.y};
    }

    TTransform2D<float> SCamera::viewToWorld(const TTransform2D<float>& viewTransform) const noexcept
    {
        const SVector2f windowSize {render::getResolution()};
        const SMatrix3f screenToNDC {
            2.f / windowSize.x, 0.f, -1.f,
            0.f, -2.f / windowSize.y, 1.f,
            0.f, 0.f, 1.f
        };
        const SMatrix3f invViewProj {(getProjectionMatrix() * getViewMatrix()).inverse()};
        return {invViewProj * screenToNDC * viewTransform.getMatrix()};
    }
}
