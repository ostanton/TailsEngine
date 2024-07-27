#include <Tails/States/LevelState.hpp>
#include <Tails/Entities/Entity.hpp>
#include <Tails/Layers/WorldLayer.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include "Tails/Engine.hpp"
#include "Tails/Subsystems/LayerSubsystem.hpp"

namespace tails
{
    Entity* LevelState::spawnEntity(std::unique_ptr<Entity> entity)
    {
        if (!entity) return nullptr;

        m_entities.emplace_back(std::move(entity));
        auto back = m_entities.back().get();
        back->outer = this;
        back->spawn();
        return back;
    }

    void LevelState::preTick()
    {
        Tickable::preTick();

        for (auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate)
            {
                entity->pendingCreate = false;
                entity->postSpawn();
                // TODO - might want to move this somewhere else?
                // it is here because contexts are removed on postTick, so adding a context of the same name
                // as one being removed executes after (preTick) the one being removed (postTick)
                entity->setupInput(getWorld().getLayerSubsystem().getEngine().getInputSubsystem());
            }
        }
    }

    void LevelState::tick(float deltaTime)
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate)
                entity->tick(deltaTime);
        }
    }

    void LevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate)
                target.draw(*entity, states);
        }
    }

    void LevelState::postTick()
    {
        Tickable::postTick();

        for (auto it = m_entities.rbegin(); it != m_entities.rend();)
        {
            it->get()->postTick();

            if (it->get()->pendingDestroy)
                m_entities.erase(it.base());
            else
                ++it;
        }
    }

    void LevelState::destroyEntity(Entity* entity)
    {
        if (auto it = std::find_if(m_entities.begin(), m_entities.end(),
            [&](auto& uniqueEntity)
            {
                return uniqueEntity.get() == entity;
            }); it == m_entities.end())
            return;

        entity->pendingDestroy = true;
        entity->despawn();
    }

    WorldLayer& LevelState::getWorld() const
    {
        return *dynamic_cast<WorldLayer*>(outer);
    }

    void LevelState::loadFromFile(std::string levelFile)
    {
        // TODO - load level from file, obviously
    }
} // tails