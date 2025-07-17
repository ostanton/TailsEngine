#include <Tails/World/Components/CameraComponent.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/World/Level.hpp>

namespace tails
{
    CCameraComponent::CCameraComponent()
    {
        collisionType = ECollisionType::None;
    }

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

    void CCameraComponent::onInit()
    {
        CComponent::onInit();

        const auto worldPosition = getWorldPosition();
        m_targetPosition = worldPosition;

        if (inheritPosition)
            camera.position = m_targetPosition;

        if (inheritRotation)
            camera.rotation = getWorldRotation();

        if (inheritScale)
            camera.zoom = getWorldScale().length();
    }

    void CCameraComponent::onTick(const float deltaSeconds)
    {
        CComponent::onTick(deltaSeconds);

        if (inheritPosition)
        {
            const auto worldPosition = getWorldPosition();

            // smooth the position
            if (enableLag)
                m_targetPosition = maths::lerp(m_targetPosition, worldPosition, lagSpeed * deltaSeconds);
            else
                m_targetPosition = worldPosition;

            camera.position = m_targetPosition;
        }

        if (inheritRotation)
            camera.rotation = getWorldRotation();

        if (inheritScale)
            camera.zoom = getWorldScale().length();
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
