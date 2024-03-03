#include "TailsEngine/Core/Level.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Level/CollisionTest.h"
#include "TailsEngine/Level/TailsEntity.h"
#include "TailsEngine/Managers/CollisionManager.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

void tails::Level::construct()
{
    Object::construct();

    m_assetCache.reset(new AssetCache);

    /*
     * Load texture for both entities to use
     * I suppose if only the player was using this texture, then it could load it instead
     */
    getAssetCache().loadTexture("tails", "Assets/Textures/Tails.png");

    // loop entities in .json and create them ready for create() to spawn them
    //getWorld()->createEntity<TailsEntity>(this);
    //getWorld()->createEntity<CollisionTest>(this);

    createEntity<TailsEntity>({480.f, 320.f});
    createEntity<CollisionTest>({400.f, 400.f});
    createEntity<CollisionTest>({300.f, 300.f});
}

tails::World* tails::Level::getWorld() const
{
    return dynamic_cast<World*>(outer);
}

tails::AssetCache& tails::Level::getAssetCache() const
{
    return *m_assetCache;
}

tails::MusicManager& tails::Level::getMusicManager()
{
    return m_musicManager;
}

void tails::Level::spawnEntity(Entity* entityToSpawn)
{
    entityToSpawn->spawn();
}

void tails::Level::destroyEntity(Entity* entityToDestroy)
{
    const auto iter = std::find_if(
        m_entities.begin(), m_entities.end(),
        [entityToDestroy] (const unique_ptr<Entity>& entity)
    {
        return entity.get() == entityToDestroy;
    });

    if (iter != m_entities.end())
    {
        entityToDestroy->despawn();
        m_entities.erase(iter);
    }
}

void tails::Level::create()
{
    spawnEntities();

    postSpawn();
}

void tails::Level::spawnEntities()
{
    for (auto& createdEntity : m_entities)
    {
        spawnEntity(createdEntity.get());
    }
}

void tails::Level::postSpawn()
{
    
}

void tails::Level::update(float deltaTime)
{
    for (size_t i {0}; i < m_entities.size(); i++)
    {
        m_entities[i]->update(deltaTime);

        for (size_t e {0}; e < m_entities.size(); e++)
        {
            if (m_entities[i] != m_entities[e])
                CollisionManager::checkCollision(m_entities[i].get(), m_entities[e].get());
        }
    }
}

void tails::Level::processInput(sf::Event& e)
{
    if (m_entities.empty())
        return;

    for (size_t i {0}; i < m_entities.size(); i++)
    {
        m_entities[i]->processInput(e);
    }
}

void tails::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < m_entities.size(); i++)
    {
        target.draw(*m_entities[i]);
    }
}

void tails::Level::cleanupEntities()
{
    for (auto& createdEntity : m_entities)
    {
        if (!createdEntity)
            continue;
        
        if (createdEntity->m_pendingDestroy)
        {
            destroyEntity(createdEntity.get());
        }
    }
}
