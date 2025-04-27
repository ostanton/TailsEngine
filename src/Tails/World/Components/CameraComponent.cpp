#include <Tails/World/Components/CameraComponent.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>

namespace tails
{
    void CCameraComponent::activate()
    {
        auto const owner = getOwner();
        if (!owner)
            return;

        auto const level = owner->getLevel();
        if (!level)
            return;

        level->activeCamera = this;
    }

    bool CCameraComponent::isActive() const noexcept
    {
        auto const owner = getOwner();
        if (!owner)
            return false;

        auto const level = owner->getLevel();
        if (!level)
            return false;

        return level->activeCamera == this;
    }

    void CCameraComponent::onTick(float deltaSeconds)
    {
    }
}
