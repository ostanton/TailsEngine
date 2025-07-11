#include <Tails/World/Camera.hpp>

#include <numbers>

namespace tails
{
    void SCamera::rotate(const float degrees) noexcept
    {
        rotation += degrees * std::numbers::pi / 180.0;
    }

    float SCamera::getRotationDegrees() const noexcept
    {
        return rotation * 180.0 / std::numbers::pi;
    }
}
