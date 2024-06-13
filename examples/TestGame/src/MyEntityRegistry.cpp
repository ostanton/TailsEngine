#include <TestGame/MyEntityRegistry.hpp>
#include <TestGame/MyEntity.hpp>

void MyEntityRegistry::init(tails::RegistrySubsystem& subsystem)
{
    EntityRegistry::init(subsystem);

    assignRegistrar<MyEntity>("my-entity");
}
