#include <Tails/World/Camera.hpp>
#include <Tails/Maths/Vector3.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Window.hpp>

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

    /**
     * TODO - we probably want the renderer resolution, not window size,
     * however, if we do that, the first frame needs to update the renderer somehow,
     * otherwise its size is 0, and we display nothing!
     */
    static SVector2f getWindowSize() {return SVector2f {window::getSize()};}

    SMatrix3f SCamera::getProjectionMatrix() const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const float windowAspect {windowSize.x / windowSize.y};
        const float halfHeight {height * 0.5f / zoom};
        const float halfWidth {halfHeight * windowAspect};

        const float left {-halfWidth};
        const float right {halfWidth};
        const float bottom {-halfHeight};
        const float top {halfHeight};

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

        const SVector2f windowSize {getWindowSize()};
        return {
            (ndc.x + 1.f) * 0.5f * windowSize.x,
            (1.f - (ndc.y + 1.f) * 0.5f) * windowSize.y
        };
    }

    SFloatRect SCamera::worldToView(const SFloatRect& worldRect) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const SMatrix3f ndcToScreen {
            windowSize.x / 2.f, 0.f, windowSize.x / 2.f,
            0.f, -windowSize.y / 2.f, windowSize.y / 2.f,
            0.f, 0.f, 1.f
        };
        return SMatrix3f {ndcToScreen * getProjectionMatrix() * getViewMatrix()}.transform(worldRect);
    }

    SFloatOrientedRect SCamera::worldToView(const SFloatOrientedRect& worldRect) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const SMatrix3f ndcToScreen {
            windowSize.x / 2.f, 0.f, windowSize.x / 2.f,
            0.f, -windowSize.y / 2.f, windowSize.y / 2.f,
            0.f, 0.f, 1.f
        };

        const SMatrix3f worldToScreen {ndcToScreen * getProjectionMatrix() * getViewMatrix()};

        const SVector2f screenAxisX {worldToScreen.transformAngle(worldRect.axisX)};
        const SVector2f screenAxisY {worldToScreen.transformAngle(worldRect.axisY)};

        const SVector2f scale {screenAxisX.length(), screenAxisY.length()};

        return {
            worldToScreen.transform(worldRect.centre),
            screenAxisX / scale.x,
            screenAxisY / scale.y,
            worldRect.halfExtents * scale
        };
    }

    STransform2D SCamera::worldToView(const STransform2D& worldTransform) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};

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
        const SVector2f windowSize {getWindowSize()};
        const SVector2f ndc {
            viewPoint.x / windowSize.x * 2.f - 1.f,
            -(viewPoint.y / windowSize.y * 2.f - 1.f)
        };

        const SVector3f ndcPoint {ndc.x, ndc.y, 1.f};
        const SMatrix3f invWorldToNDC {(getProjectionMatrix() * getViewMatrix()).inverse()};
        const SVector3f worldPoint {invWorldToNDC * ndcPoint};
        return {worldPoint.x, worldPoint.y};
    }

    SFloatRect SCamera::viewToWorld(const SFloatRect& viewRect) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const SMatrix3f screenToNDC {
            2.f / windowSize.x, 0.f, -1.f,
            0.f, -2.f / windowSize.y, 1.f,
            0.f, 0.f, 1.f
        };
        const SMatrix3f invViewProj {(getProjectionMatrix() * getViewMatrix()).inverse()};
        return SMatrix3f {invViewProj * screenToNDC}.transform(viewRect);
    }

    SFloatOrientedRect SCamera::viewToWorld(const SFloatOrientedRect& viewRect) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const SMatrix3f screenToNDC {
            2.f / windowSize.x, 0.f, -1.f,
            0.f, -2.f / windowSize.y, 1.f,
            0.f, 0.f, 1.f
        };
        const SMatrix3f screenToWorld {(getProjectionMatrix() * getViewMatrix()).inverse() * screenToNDC};

        const SVector2f worldAxisX {screenToWorld.transformAngle(viewRect.axisX)};
        const SVector2f worldAxisY {screenToWorld.transformAngle(viewRect.axisY)};

        const SVector2f scale {worldAxisX.length(), worldAxisY.length()};

        return {
            screenToWorld.transform(viewRect.centre),
            worldAxisX / scale.x,
            worldAxisY / scale.y,
            viewRect.halfExtents * scale
        };
    }

    STransform2D SCamera::viewToWorld(const STransform2D& viewTransform) const noexcept
    {
        const SVector2f windowSize {getWindowSize()};
        const SMatrix3f screenToNDC {
            2.f / windowSize.x, 0.f, -1.f,
            0.f, -2.f / windowSize.y, 1.f,
            0.f, 0.f, 1.f
        };
        const SMatrix3f invViewProj {(getProjectionMatrix() * getViewMatrix()).inverse()};
        return {invViewProj * screenToNDC * viewTransform.getMatrix()};
    }
}
