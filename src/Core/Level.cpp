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

    Debug::log("Level construct");

    m_constructed = true;
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

bool tails::Level::isReady() const
{
    return m_constructed && m_entitiesSpawned;
}

void tails::Level::spawnEntity(Entity* entityToSpawn)
{
    m_spawnedEntities.emplace_back(entityToSpawn);
    entityToSpawn->spawn();
}

void tails::Level::despawnEntity(Entity* entityToDespawn)
{
    const std::vector<Entity*>::const_iterator entityIter =
        std::find(m_spawnedEntities.begin(), m_spawnedEntities.end(), entityToDespawn);
    
    if (entityIter != m_spawnedEntities.end())
    {
        entityToDespawn->despawn();
        m_spawnedEntities.erase(entityIter);
    }
}

void tails::Level::destroyEntity(Entity* entityToDestroy)
{
    despawnEntity(entityToDestroy);
    
    const auto iter = std::find_if(
        m_createdEntities.begin(), m_createdEntities.end(),
        [entityToDestroy] (const unique_ptr<Entity>& entity)
    {
        return entity.get() == entityToDestroy;
    });

    if (iter != m_createdEntities.end())
    {
        m_createdEntities.erase(iter);
    }
}

const std::vector<tails::Entity*>& tails::Level::getSpawnedEntities() const
{
    return m_spawnedEntities;
}

void tails::Level::create()
{
    //Debug::log("Level create");

    spawnEntities();

    postSpawn();
}

void tails::Level::spawnEntities()
{
    for (auto& createdEntity : m_createdEntities)
    {
        spawnEntity(createdEntity.get());
    }
}

void tails::Level::postSpawn()
{
    m_entitiesSpawned = true;
    //Debug::log("Level postSpawn");
    Debug::log("Usage of tails: " + std::to_string(getAssetCache()["tails"].getUsageCount()));
}

void tails::Level::update(float deltaTime)
{
    //Debug::log("Level update");
    for (size_t i {0}; i < m_spawnedEntities.size(); i++)
    {
        if (m_spawnedEntities[i]->isSpawned() && isObjectValid(m_spawnedEntities[i]))
        {
            m_spawnedEntities[i]->update(deltaTime);

            for (size_t e {0}; e < m_spawnedEntities.size(); e++)
            {
                if (m_spawnedEntities[e]->isSpawned() && isObjectValid(m_spawnedEntities[e]))
                    // Check collision between entities if they are different objects
                    if (m_spawnedEntities[i] != m_spawnedEntities[e])
                        CollisionManager::checkCollision(m_spawnedEntities[i], m_spawnedEntities[e]);
            }
        }
    }
}

// TODO - this is being called whilst the level is constructing??
// it goes from construct straight to update or processInput. Probably not having create called? Or main loop
// trying to make it so it's always updating?
void tails::Level::processInput(sf::Event& e)
{
    //Debug::log("Level processInput");
    if (m_spawnedEntities.empty())
        return;

    // TODO - this seems to work but crashed once. Can't replicate
    for (size_t i {0}; i < m_spawnedEntities.size(); i++)
    {
        if (m_spawnedEntities[i]->isSpawned() && isObjectValid(m_spawnedEntities[i]))
            m_spawnedEntities[i]->processInput(e);
    }

    //for (const auto& entity : entities)
    //{
    //    entity->processInput(e);
    //}
}

void tails::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Debug::log("Level draw");
    for (size_t i {0}; i < m_spawnedEntities.size(); i++)
    {
        if (m_spawnedEntities[i]->isSpawned() && isObjectValid(m_spawnedEntities[i]))
            target.draw(*m_spawnedEntities[i]);
    }
}
