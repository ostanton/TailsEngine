#pragma once
#include <vector>

#include "Obj.h"
#include "TailsEngine/Core/Entity.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"
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
enum class InputMode;
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
 * to be used as an input into World's openLevel() and createAndOpenLevel() methods. It holds the .json of the
 * current level. Maybe we don't even need to destroy or create this class to load a level, just empty its contents.
 * Do we need a World class at that point?
 *
 * Could we just have a loadLevel() method which takes in a string path to the .json file, and load that after
 * cleaning up whatever stuff shouldn't be carried over? Remove entities, clean out the asset cache, etc.
 *
 * What if this Level class didn't exist, and there was just the World class with some kind of .json reference for its
 * current level. It is just easier to have a Level class to manage entities and the .json files, then a World class
 * to manage the Level class.
 *
 * So:
 * - World holds lifetime of Level, creation, opening, loading, deletion, etc.
 * - Level holds lifetime of Entity and .json level. Which means you can load a new Level class object from the World,
 * which effectively resets everything, starting fresh (like openLevel in Unreal), OR you can just load another .json
 * level, which keeps the state of this Level object intact, it just looks like you're loading a new level from the
 * player's view.
 *
 * TODO:
 * Here's the thing. We can't createEntity() with its template being from the json, as templates are done at
 * compile-time, not run-time. So how do we fix this? Macros? Some kind of forcing it to accept it or something?
 * Somehow we need to make entities of a specific type that derives from Entity. We can't make a new Entity from
 * a "json object" or something can we? How would this work? Help!
 */
class Level final : public Object, public sf::Drawable, public sf::Transformable
{
    friend World;

public:
    void loadJson();
    
    // TODO - tileMap or whatever members
    // specific .json ldtk level file

    void construct() override;
    
    /**
     * \brief Gets the world that holds this level
     * \return Pointer to the world
     */
    World& getWorld() const;

    AssetCache& getAssetCache();
    MusicManager& getMusicManager();

    Viewport& getViewport() const;

    template<typename EntT>
    EntT* spawnEntity()
    {
        return spawnEntity<EntT>(sf::Vector2f(0.f, 0.f));
    }

    /**
     * \brief Spawns an entity at the specified position, angle and scale, and adds it to the entities vector.
     * This entity is now in the level and updates and draws as expected starting next frame
     * \tparam EntT Entity type
     * \param position Position in level
     * \param angle Entity rotation [Default = 0.f]
     * \param scale Entity scale [Default = {1.f, 1.f}]
     * \return Pointer to created Entity object
     */
    template<typename EntT>
    EntT* spawnEntity(const sf::Vector2f& position, const float angle = 0.f, const sf::Vector2f& scale = {1.f, 1.f})
    {
        Entity* resultEntity {createEntity<EntT>(position, angle, scale)};
        spawnEntity(resultEntity);
        return dynamic_cast<EntT*>(resultEntity);
    }

    void spawnEntity(Entity* entityToSpawn);

    void setInputMode(InputMode inputMode) const;

    void setViewCameraPosition(const sf::Vector2f& position) const;

    void pauseGame(bool pause) const;
    
protected:
    /**
     * \brief Completely removes the specified entity from the Level if it is spawned, and deletes its memory.
     * Should not be called manually, instead mark the entity for destruction with its own destroy() method.
     * This method acts as a kind of garbage collection for those entities marked for destruction. It is called
     * at the end of each frame for any Entity marked for destruction
     * \param entityToDestroy The entity to destroy
     */
    void destroyEntity(const unique_ptr<Entity>& entityToDestroy);
    
    /**
     * \brief Called when this level is created and its members should all be initialised
     */
    void create();
    void spawnEntities();
    /**
     * \brief Called once all entities have been spawned
     */
    void postSpawn();
    /**
     * \brief Called every frame this level is alive
     * \param deltaTime Time since last frame
     */
    void update(float deltaTime);
    void processInput(sf::Event& e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * \brief Creates an Entity object at specified position, angle and scale. Does not add to a smart pointer.
     * Prefer to use templated spawnEntity() instead
     * \tparam EntT Entity type
     * \param position Position in level
     * \param angle Entity rotation [Default = 0.f]
     * \param scale Entity scale [Default = {1.f, 1.f}]
     * \return Pointer to created Entity object
     */
    template<typename EntT>
    EntT* createEntity(const sf::Vector2f& position, const float angle = 0.f, const sf::Vector2f& scale = {1.f, 1.f})
    {
        static_assert(std::is_base_of_v<Entity, EntT>, "Entity must be of subclass Entity to be created");
        
        Entity* resultEntity { newObject<EntT>(this) };

        resultEntity->setPosition(position);
        resultEntity->setRotation(angle);
        resultEntity->setScale(scale);

        resultEntity->create();

        return dynamic_cast<EntT*>(resultEntity);
    }

private:
    AssetCache m_assetCache;
    MusicManager m_musicManager;

    /**
     * \brief The vector of all the entities created in this level. Not all of these entities could be spawned,
     * so use "entities" for all the spawned entities instead
     */
    std::vector<unique_ptr<Entity>> m_entities;

    /**
     * \brief A vector of entities that are waiting till the next frame to spawn
     */
    std::vector<unique_ptr<Entity>> m_entitiesPendingSpawn;

    /**
     * \brief Spawn any created entities that are pending spawn from m_entitiesPendingSpawn
     */
    void setupData() override;
    void cleanupData() override;
    
    /**
     * \brief Destroys any entities that are marked for destruction
     */
    void cleanupEntities();
};

}
