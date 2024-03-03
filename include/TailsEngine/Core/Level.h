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
#include "TailsEngine/Level/Entity.h"
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
 */
class Level final : public Object, public sf::Drawable
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

    AssetCache& getAssetCache() const;
    MusicManager& getMusicManager();

    template<typename EntT>
    EntT* spawnEntity()
    {
        return spawnEntity<EntT>(sf::Vector2f(0.f, 0.f));
    }

    /**
     * \brief Spawns an entity at the specified position, angle and scale, and adds it to the entities vector.
     * This entity is now in the level and updates and draws as expected
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

    /**
     * \brief Completely removes the specified entity from the Level if it is spawned, and deletes its memory
     * \param entityToDestroy The entity to destroy
     */
    void destroyEntity(Entity* entityToDestroy);
    
protected:
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
     * \brief Creates an Entity object at specified position, angle and scale, and adds it to the m_createdEntities
     * vector. It does not spawn the entity
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
        
        m_entities.emplace_back(resultEntity);

        resultEntity->create();

        return dynamic_cast<EntT*>(resultEntity);
    }

private:
    unique_ptr<AssetCache> m_assetCache;
    MusicManager m_musicManager;

    /**
     * \brief The vector of all the entities created in this level. Not all of these entities could be spawned,
     * so use "entities" for all the spawned entities instead
     */
    std::vector<unique_ptr<Entity>> m_entities;

    /**
     * \brief Destroys any entities that are marked for destruction
     */
    void cleanupEntities();
};

}
