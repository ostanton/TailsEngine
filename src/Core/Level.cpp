#include "TailsEngine/Core/Level.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Temp/CollisionTest.h"
#include "TailsEngine/Temp/TailsEntity.h"
#include "TailsEngine/Managers/CollisionManager.h"

void tails::Level::construct()
{
    Object::construct();

    /*
     * Load texture for both entities to use
     * I suppose if only the player was using this texture, then it could load it instead
     */
    getAssetCache().loadTexture("tails", "Assets/Textures/Tails.png");
    getAssetCache().loadTexture("pointer", "Assets/Textures/Pointer.png");
    getAssetCache().loadTexture("tails_running", "Assets/Textures/TailsRunning.png");

    // loop entities in .json and create them ready for create() to spawn them

    spawnEntity<TailsEntity>({480.f, 320.f});
    spawnEntity<CollisionTest>({400.f, 400.f});
    spawnEntity<CollisionTest>({300.f, 300.f});

    // TODO - use decltype() to spawn entities??? Someone how make classes from the json, then use stack objects in
    // decltype for the template to spawn them in the level
    TailsEntity tailsEntity;
    spawnEntity<decltype(tailsEntity)>({0.f, 0.f});
}

tails::World& tails::Level::getWorld() const
{
    return *dynamic_cast<World*>(outer);
}

tails::AssetCache& tails::Level::getAssetCache()
{
    return m_assetCache;
}

tails::MusicManager& tails::Level::getMusicManager()
{
    return m_musicManager;
}

tails::Viewport& tails::Level::getViewport() const
{
    return getWorld().getViewport();
}

void tails::Level::spawnEntity(Entity* entityToSpawn)
{
    // This only temporarily adds the entity to spawn into the pending spawn vector for use start of next frame
    m_entitiesPendingSpawn.emplace_back(entityToSpawn);
}

void tails::Level::destroyEntity(const unique_ptr<Entity>& entityToDestroy)
{
    const auto iter =
        std::find(m_entities.begin(), m_entities.end(), entityToDestroy);
    
    if (iter != m_entities.end())
    {
        entityToDestroy->despawn();
        m_entities.erase(iter);
    }
}

void tails::Level::create()
{
    
}

void tails::Level::spawnEntities()
{
    if (m_entitiesPendingSpawn.empty())
        return;

    /**
     * Where the "actual" spawning happens. At the start of the frame, move the pending spawn entities into the main
     * entities vector. This entities vector is what updates and draws the entities, hence them being "spawned"
     */
    for (auto& createdEntity : m_entitiesPendingSpawn)
    {
        createdEntity->spawn();
        m_entities.emplace_back(std::move(createdEntity));
    }

    m_entitiesPendingSpawn.clear();
}

void tails::Level::postSpawn()
{
    if (m_entities.empty())
        return;
    
    for (const auto& entity : m_entities)
    {
        entity->setupData();
    }
}

void tails::Level::update(float deltaTime)
{
    for (size_t i {0}; i < m_entities.size(); i++)
    {
        m_entities[i]->update(deltaTime);

        // Loop within a loop to check collision between entities. Is there a better way?
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
        states.transform *= getTransform();
        target.draw(*m_entities[i], states);
    }
}

void tails::Level::setupData()
{
    spawnEntities();
    postSpawn();
}

void tails::Level::cleanupData()
{
    // Could put entity's own cleanupData() method here? Does it need one? Or put it in cleanupEntities() actually
    cleanupEntities();
}

void tails::Level::cleanupEntities()
{
    for (auto& createdEntity : m_entities)
    {
        if (!createdEntity)
            continue;

        createdEntity->cleanupData();
        
        if (createdEntity->m_pendingDestroy)
        {
            destroyEntity(createdEntity);
        }
    }
}
