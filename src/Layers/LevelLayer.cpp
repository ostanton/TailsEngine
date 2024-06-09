#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Engine.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

namespace tails
{
    void LevelLayer::spawnEntity(const std::string& name)
    {
        // get entity registry and clone it into the entity vector
    }

    void LevelLayer::loadJson(const std::string& path)
    {
        /*
        EntityRegistry* registry = getState().getStateSubsystem().getEngine().getSubsystem<RegistrySubsystem>("registry")->getRegistry<EntityRegistry>("entity");
        */
        std::ifstream file(path);
        json data = json::parse(file);

        for (auto& obj : data["entities"])
        {
            spawnEntity(obj.get<std::string>());
        }
    }
}
