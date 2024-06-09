#include <Tails/Registries/EntityRegistry.hpp>
#include <Tails/Entities/SpriteEntity.hpp>

namespace tails
{
    void EntityRegistry::init(RegistrySubsystem& subsystem)
    {
        assignRegistrar<SpriteEntity>("sprite");
    }
}
