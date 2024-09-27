#include <Tails/Component.hpp>
#include <Tails/Entity.hpp>

namespace tails
{
    CEntity* CComponent::getOwningEntity() const
    {
        return getTypedOuter<CEntity>();
    }
}
