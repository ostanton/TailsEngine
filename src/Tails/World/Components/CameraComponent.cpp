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

        level->setActiveCamera(this);
    }

    bool CCameraComponent::isActive() const noexcept
    {
        auto const owner = getOwner();
        if (!owner)
            return false;

        auto const level = owner->getLevel();
        if (!level)
            return false;

        return &level->getActiveCamera() == &camera;
    }

    void CCameraComponent::onTick(const float deltaSeconds)
    {
        CComponent::onTick(deltaSeconds);

        camera.position = getWorldPosition();
        camera.rotation = getWorldRotation();
    }

    void CCameraComponent::onDeinit()
    {
        CComponent::onDeinit();

        if (auto const level = getLevel();
            isActive() && level)
        {
            // tell the level to switch to another camera because we just got destroyed
            level->setActiveCamera(nullptr);
        }
    }
}
