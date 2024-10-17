#include <Tails/CameraComponent.hpp>
#include <Tails/Level.hpp>
#include <Tails/Entity.hpp>

#include <SFML/Graphics/RenderStates.hpp>

namespace tails
{
    void CCameraComponent::setActive()
    {
        getOwningEntity().getLevel().setActiveCamera(this);
    }

    bool CCameraComponent::isActive() const
    {
        return getOwningEntity().getLevel().isCameraActive(this);
    }

    void CCameraComponent::create()
    {
        CComponent::create();

        m_view = getOwningEntity().getLevel().getActiveCameraView();
    }

    void CCameraComponent::tick(float deltaTime)
    {
        CComponent::tick(deltaTime);
        m_view.setCenter(getOwningEntity().getPosition());
    }
}
