#include <Tails/World/Camera.hpp>
#include <Tails/Renderer/Renderer.hpp>

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
        const float worldHeight {100.f / zoom};
        const SVector2f viewSize {1000.f, 1000.f};
        const float aspectRatio {viewSize.x / viewSize.y};
        const float worldWidth {worldHeight * aspectRatio};

        const SVector2f halfView {worldWidth * 0.5f, worldHeight * 0.5f};

        return {
            1.f / halfView.x, 0.f, 0.f,
            0.f, 1.f / halfView.y, 0.f,
            0.f, 0.f, 1.f
        };
    }

    SVector2f SCamera::getViewSize() const noexcept
    {
        return render::getResolution() / zoom;
    }

    TTransform2D<float> SCamera::worldToView(const TTransform2D<float>& transform) const noexcept
    {
        const auto screenMatrix = transform.getMatrix() * getViewMatrix() * getProjectionMatrix();

        STransform2D screenTransform {screenMatrix};
        const auto ndc = screenTransform.getPosition();

        const SVector2f viewSize {1000.f, 1000.f};

        // convert normalised device coordinates to screen pixels
        screenTransform.setPosition({
            (ndc.x + 1.f) * 0.5f * viewSize.x,
            (1.f - (ndc.y + 1.f) * 0.5f) * viewSize.y
        });
        return screenTransform;
    }
}
