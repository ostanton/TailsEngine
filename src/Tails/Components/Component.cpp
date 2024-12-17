#include <Tails/Components/Component.hpp>
#include <Tails/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CEntity& CComponent::getOwningEntity() const
    {
        // components should never not have a valid owning entity
        return *getTypedOuter<CEntity>();
    }
}
