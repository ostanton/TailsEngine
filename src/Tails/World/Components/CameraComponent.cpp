#include <Tails/World/Components/CameraComponent.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>

namespace tails
{
    SFloatRect CCameraComponent::getGlobalBounds() const noexcept
    {
        return {
            transform.position + bounds.position,
            transform.position + bounds.size
        };
    }

    void CCameraComponent::activate()
    {
        auto const owner = getOwningActor();
        if (!owner)
            return;

        auto const level = owner->getLevel();
        if (!level)
            return;

        level->activeCamera = this;
    }

    bool CCameraComponent::isActive() const noexcept
    {
        auto const owner = getOwningActor();
        if (!owner)
            return false;

        auto const level = owner->getLevel();
        if (!level)
            return false;

        return level->activeCamera == this;
    }
}
