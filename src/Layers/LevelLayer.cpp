#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Engine.hpp>

#include <fstream>
#include <json.h>

namespace tails
{
    void LevelLayer::spawnEntity(const std::string& name)
    {
        // get entity registry and clone it into the entity vector
        // entityRegistry->loadRegistrar(name, inJson);
    }

    void LevelLayer::loadJson(const std::string& path)
    {
        /*
        EntityRegistry* registry = getState().getStateSubsystem().getEngine().getSubsystem<RegistrySubsystem>("registry")->getRegistry<EntityRegistry>("entity");
        */
    }
}
