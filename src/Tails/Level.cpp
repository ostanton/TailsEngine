#include <Tails/Level.hpp>
#include <Tails/World.hpp>
#include <Tails/Entity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    CLevel::~CLevel() = default;

    void CLevel::destroyEntity(CEntity* entity)
    {
        entity->destroy();
    }

    CWorld& CLevel::getWorld() const
    {
        return *static_cast<CWorld*>(outer);
    }

    CEngine& CLevel::getEngine() const
    {
        return getWorld().getEngine();
    }

    CLevel::CLevel(std::string path)
        : m_path(std::move(path))
    {
        
    }

    void CLevel::preTick()
    {
        ITickable::preTick();

        for (auto& entity : m_entities)
        {
            entity->preTick();

            if (entity->pendingCreate())
            {
                entity->unmarkForCreate();
                entity->postSpawn();
            }
        }
    }

    void CLevel::tick(float deltaTime)
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate())
                entity->tick(deltaTime);
        }
    }

    void CLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (auto& entity : m_entities)
        {
            if (!entity->pendingCreate())
                target.draw(*entity, states);
        }
    }

    void CLevel::postTick()
    {
        ITickable::postTick();

        for (auto it = m_entities.rbegin(); it != m_entities.rend();)
        {
            it->get()->postTick();

            if (it->get()->pendingDestroy())
                it = decltype(it)(m_entities.erase(std::next(it).base()));
            else
                ++it;
        }
    }

    CEntity* CLevel::spawnEntityImpl(std::unique_ptr<CEntity> entity)
    {
        entity->outer = this;
        entity->spawn();

        m_entities.emplace_back(std::move(entity));

        return m_entities.back().get();
    }
}
