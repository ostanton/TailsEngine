#include "TailsEngine/Core/Level.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Level/CollisionTest.h"
#include "TailsEngine/Level/TailsEntity.h"
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
    getWorld()->createEntity<TailsEntity>(this);
    getWorld()->createEntity<CollisionTest>(this);

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

void tails::Level::create()
{
    Debug::log("Level create");
    // "spawn" every entity
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->spawn();
    }

    postSpawn();
}

void tails::Level::postSpawn()
{
    m_entitiesSpawned = true;
    Debug::log("Level postSpawn");
    Debug::log("Usage of tails: " + std::to_string(getAssetCache()["tails"].getUsageCount()));
}

void tails::Level::update(float deltaTime)
{
    Debug::log("Level update");
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
    }
}

// TODO - this is being called whilst the level is constructing??
// it goes from construct straight to update or processInput. Probably not having create called? Or main loop
// trying to make it so it's always updating?
void tails::Level::processInput(sf::Event& e)
{
    Debug::log("Level processInput");
    if (entities.empty())
        return;

    // TODO - this seems to work but crashed once. Can't replicate
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->processInput(e);
    }

    //for (const auto& entity : entities)
    //{
    //    entity->processInput(e);
    //}
}

void tails::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < entities.size(); i++)
    {
        target.draw(*entities[i]);
    }
}
