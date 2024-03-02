#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
// TODO - need these includes for it to compile for some reason??
// use of undefined type "tails::AssetCache"
// static_assert failed: "can't delete an incomplete type"
// deletion of pointer to incomplete type "tails::AssetCache"; no destructor called
#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

#include "Obj.h"
#include "TailsEngine/Managers/MusicManager.h"

namespace sf
{
class Event;
}

namespace tails
{
class Entity;
class World;
class AssetCache;
}

namespace tails
{
/**
 * \brief A class that holds a vector of entities, and generally shouldn't have specialised subclasses.
 * A Level's visuals are represented via its tile map, which will probably be set upon its creation or load from
 * the resource manager. Something like
 *
 * getResourceManager().tileMapManager.getAsset("level1")
 *
 * to be used as an input into World's openLevel() and createAndOpenLevel() methods
 */
class Level : public Object, public sf::Drawable
{
    friend World;

public:
    // TODO - tileMap or whatever members
    // specific .json ldtk level file

    void construct() override;
    
    /**
     * \brief Gets the world that holds this level
     * \return Pointer to the world
     */
    World* getWorld() const;

    /**
     * \brief The entities contained within this level to draw, update, etc.
     */
    std::vector<unique_ptr<Entity>> entities;

    AssetCache& getAssetCache() const;
    MusicManager& getMusicManager();

    /**
     * \brief Gets whether this level can be updated and drawn, whether it is "ready" for that or still needs
     * some members initialised and set
     * \return Ready or not
     */
    bool isReady() const;
    
protected:
    /**
     * \brief Called when this level is created and its members should all be initialised
     */
    virtual void create();
    /**
     * \brief Called once all entities have been spawned
     */
    virtual void postSpawn();
    /**
     * \brief Called every frame this level is alive
     * \param deltaTime Time since last frame
     */
    virtual void update(float deltaTime);
    virtual void processInput(sf::Event& e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    unique_ptr<AssetCache> m_assetCache;
    MusicManager m_musicManager;

    // TODO - BOTCHED! THIS FEELS VERY BOTCHED AND LIKE IT SHOULDN'T BE THE WAY TO MAKE THINGS WORK HELP
    bool m_constructed {false};
    bool m_entitiesSpawned {false};
};

}
