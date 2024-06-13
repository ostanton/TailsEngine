#ifndef TESTGAME_MYENTITYREGISTRY_HPP
#define TESTGAME_MYENTITYREGISTRY_HPP

#include <Tails/Registries/EntityRegistry.hpp>

class MyEntityRegistry : public tails::EntityRegistry
{
private:
    void init(tails::RegistrySubsystem& subsystem) override;
};


#endif //TESTGAME_MYENTITYREGISTRY_HPP
