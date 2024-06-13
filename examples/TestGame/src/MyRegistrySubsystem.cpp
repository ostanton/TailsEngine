#include <TestGame/MyRegistrySubsystem.hpp>
#include <TestGame/MyEntityRegistry.hpp>

void MyRegistrySubsystem::init(tails::Engine& engine)
{
    RegistrySubsystem::init(engine);

    emplaceRegistry<MyEntityRegistry>("myRegistry");
}
