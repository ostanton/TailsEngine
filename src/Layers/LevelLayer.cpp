#include <Tails/Layers/LevelLayer.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Entities/Entity.hpp>
#include <Tails/Subsystems/RegistrySubsystem.hpp>
#include <Tails/Registries/EntityRegistry.hpp>
#include <Tails/EngineStatics.hpp>
#include <Tails/Assert.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    void LevelLayer::spawnEntity(const std::string& name, nlohmann::json& value)
    {
        m_entities.emplace_back(std::move(m_registry->loadRegistrar(name, value)));

        Debug::print("Spawned " + name + "!");
    }

    Entity* LevelLayer::spawnEntity(std::unique_ptr<Entity> entity)
    {
        entity->pendingCreate = true;
        entity->outer = this;
        m_entities.push_back(std::move(entity));
        return m_entities.back().get();
    }

    Entity* LevelLayer::spawnEntity(std::unique_ptr<Entity> entity, const Transform& transform)
    {
        auto result = spawnEntity(std::move(entity));
        result->setTransform(transform);
        return result;
    }

    void LevelLayer::loadJson(const std::string& path)
    {
        //std::fstream stream {path};
        //nlohmann::json outerObj {stream};

        // level settings?
        // camera size, position, etc.
    }

    void LevelLayer::init(State& state)
    {
        m_registry = EngineStatics::getEngine(this)->getRegistrySubsystem().getRegistry<EntityRegistry>("entity");
        TailsAssert(m_registry, "Entity Registry is invalid in LevelLayer!");
    }

    void LevelLayer::preTick()
    {
        for (auto& entity : m_entities)
        {
            if (entity->pendingCreate)
            {
                entity->pendingCreate = false;
                entity->spawn();
                Debug::print("Spawned entity.");
            }

            entity->preTick();
        }
    }

    void LevelLayer::checkCollision(Entity* entity)
    {
        if (!entity) return;

        for (auto& entity2 : m_entities)
        {
            if (entity == entity2.get()) continue;

            if (entity->isCollidingWith(entity2.get()))
            {
                entity->m_currentCollidingEntity = entity2.get();

                if (entity->m_lastCollidingEntity != entity2.get())
                {
                    entity->collisionStart(entity2.get());
                }
            }
            else
            {
                if (entity->m_lastCollidingEntity == entity->m_currentCollidingEntity)
                {
                    entity->collisionEnd(entity2.get());
                    entity->m_lastCollidingEntity = entity->m_currentCollidingEntity;
                }

                entity->m_currentCollidingEntity = nullptr;
            }
        }
    }

    void LevelLayer::tick(float deltaTime)
    {
        // TODO - collision, some sort of divide and conquer of the level?
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate)
            {
                entity->tick(deltaTime);
                checkCollision(entity.get());
            }
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
