#include <Tails/Component.hpp>
#include <Tails/Entity.hpp>

namespace tails
{
    CEntity& CComponent::getOwningEntity() const
    {
        return *getTypedOuter<CEntity>();
    }

    sf::Vector2f CComponent::getGlobalPosition() const
    {
        return getOwningEntity().getTransform().transformPoint(getPosition());
    }

    sf::Angle CComponent::getGlobalRotation() const
    {
        return getOwningEntity().getRotation() + getRotation();
    }

    sf::Vector2f CComponent::getGlobalScale() const
    {
        return {
            (getOwningEntity().getScale().x - 1.f) + (getScale().x - 1.f) + 1.f,
            (getOwningEntity().getScale().y - 1.f) + (getScale().y - 1.f) + 1.f
        };
    }
}
