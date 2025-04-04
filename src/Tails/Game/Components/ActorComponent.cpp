#include <Tails/Game/Components/ActorComponent.hpp>

namespace tails
{
    CActor* CActorComponent::getOwningActor() const
    {
        return m_owningActor;
    }

    void CActorComponent::onInit()
    {
    }

    void CActorComponent::onTick(float deltaSeconds)
    {
    }
}
