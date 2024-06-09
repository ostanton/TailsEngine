#ifndef TAILS_ENTITYREGISTRY_HPP
#define TAILS_ENTITYREGISTRY_HPP

#include <Tails/Registries/Registry.hpp>
#include <Tails/Entities/Entity.hpp>

namespace tails
{
    class EntityRegistry : public Registry<Entity>
    {
    protected:
        void init(RegistrySubsystem& subsystem) override;
    };
}

#endif // TAILS_ENTITYREGISTRY_HPP
