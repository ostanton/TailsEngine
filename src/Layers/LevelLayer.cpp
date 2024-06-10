#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Entities/Entity.hpp>
#include <Tails/Subsystems/RegistrySubsystem.hpp>
#include <Tails/Registries/EntityRegistry.hpp>
#include <Tails/Entities/RectEntity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    void LevelLayer::spawnEntity(const std::string& name, const nlohmann::json& json)
    {
        // get entity registry and clone it into the entity vector
        // entityRegistry->loadRegistrar(name, inJson);

        //m_entities.emplace_back(std::make_unique<Entity>(registry->loadRegistrar(json.key(), json)));
    }

    Entity* LevelLayer::spawnEntity(std::unique_ptr<Entity> entity)
    {
        entity->pendingCreate = true;
        entity->outer = this;
        m_entities.push_back(std::move(entity));
        return m_entities.back().get();
    }

    void LevelLayer::init(State& state)
    {
        registry = getEngine().getRegistrySubsystem().getRegistry<EntityRegistry>("entity");
        spawnEntity<RectEntity>();
        Debug::print("Spawned RectEntity!");

        // load json here?
    }

    void LevelLayer::loadJson(const std::string& path)
    {
        //std::fstream stream {path};
        //nlohmann::json outerObj {stream};
    }

    void LevelLayer::preTick()
    {
        for (auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate)
            {
                entity->pendingCreate = false;
                entity->spawn();
            }
        }
    }

    void LevelLayer::tick(float deltaTime)
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate)
                entity->tick(deltaTime);
        }
    }

    void LevelLayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate)
                target.draw(*entity, states);
        }
    }

    void LevelLayer::postTick()
    {
        for (size_t i {0}; i < m_entities.size();)
        {
            m_entities[i]->postTick();

            if (m_entities[i]->pendingDestroy)
            {
                m_entities[i]->despawn();
                m_entities.erase(m_entities.begin() + i);
            }
            else
                i++;
        }
    }
}
