#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Engine.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    void LevelLayer::spawnEntity(const std::string& name, const nlohmann::json& json)
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
