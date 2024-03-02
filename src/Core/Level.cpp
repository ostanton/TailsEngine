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

void tails::Level::create()
{
    // "spawn" every entity
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->spawn();
    }

    postSpawn();
}

void tails::Level::postSpawn()
{
    Debug::log("Usage of tails: " + std::to_string(getAssetCache()["tails"].getUsageCount()));
}

void tails::Level::update(float deltaTime)
{
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->update(deltaTime);
    }
}

void tails::Level::processInput(sf::Event& e)
{
    if (entities.empty())
        return;
    
    //for (size_t i {0}; i < entities.size(); i++)
    //{
    //    if (entities[i])
    //        entities[i]->processInput(e);
    //}

    for (const auto& entity : entities)
    {
        entity->processInput(e);
    }
}

void tails::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < entities.size(); i++)
    {
        target.draw(*entities[i]);
    }
}
