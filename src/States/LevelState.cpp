#include <Tails/LevelState.hpp>
#include <Tails/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void LevelState::destroyEntity(Entity* entity)
    {
        entity->pendingDestroy = true;
    }

    void LevelState::destroyEntity(const std::unique_ptr<Entity>& entity)
    {
        destroyEntity(entity.get());
    }

    void LevelState::preTick()
    {
        for (auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate)
            {
                entity->spawn();
                std::cout << typeid(*entity).name() << " spawned.\n";
                entity->pendingCreate = false;
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
                target.draw(*entity);
        }
    }

    void LevelState::postTick()
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
