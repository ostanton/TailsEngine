#include <Tails/Registries/EntityRegistry.hpp>
#include <Tails/Entities/RectEntity.hpp>

namespace tails
{
    void EntityRegistry::init(RegistrySubsystem& subsystem)
    {
        assignRegistrar<RectEntity>("rectangle");
    }
}
