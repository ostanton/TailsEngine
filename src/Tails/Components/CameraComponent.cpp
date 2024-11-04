#include <Tails/Components/CameraComponent.hpp>
#include <Tails/Level.hpp>
#include <Tails/Entity.hpp>
#include <Tails/Maths.hpp>

namespace tails
{
    void CCameraComponent::activate()
    {
        getOwningEntity().getLevel().setActiveCamera(this);
    }

    bool CCameraComponent::isActive() const
    {
        return getOwningEntity().getLevel().isCameraActive(this);
    }

    void CCameraComponent::setLag(float lag)
    {
        m_lag = lag;
    }

    void CCameraComponent::create()
    {
        CComponent::create();

        m_view = getOwningEntity().getLevel().getActiveCameraView();
    }

    void CCameraComponent::tick(float deltaTime)
    {
        CComponent::tick(deltaTime);

        const sf::Vector2f newCentre {
            m_lag == 0.f ?
            getOwningEntity().getPosition() :
            lerp(
                m_view.getCenter(),
                getOwningEntity().getPosition(),
                deltaTime * m_lag
            )
        };

        m_view.setCenter(newCentre);
    }
}
