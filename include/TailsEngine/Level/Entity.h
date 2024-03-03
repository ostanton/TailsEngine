#pragma once
#include <vector>

#include "TailsEngine/Core/Obj.h"
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
class Event;
}

namespace tails
{
class InputManager;
class World;
class Level;
class CollisionManager;
class MusicManager;
class AssetCache;
}

namespace tails
{
/**
 * \brief Base class for all entities. Every entity is a sprite. You do not need to do sprite things however,
 * or have any appearance at all. This might be changed for a more lax sf::Drawable instead of sf::Sprite,
 * like how the widgets work (if they do actually work that is, they might not). For now it is a sprite
 *
 * Entities stay in their Level from its creation. Destroying an entity only despawns it. It still exists in memory
 */
class Entity : public Object, public sf::Sprite
{
    friend World;
    friend Level;
    friend CollisionManager;

public:
    /**
     * \brief Destroys this entity. Deletes its memory, removes it from Level, etc.
     */
    void destroy();

protected:
    /**
     * \brief Called when this entity has been created in the level, but not yet spawned. Its position and general
     * SFML settings should be set, but it will not be in the Level's entities vector
     */
    virtual void create();
    /**
     * \brief Called once this entity has completely spawned in a level. All its members should be initialised
     */
    virtual void spawn();
    
    /**
     * \brief Called every frame that this entity is alive
     * \param deltaTime Time since last frame
     */
    virtual void update(float deltaTime);

    virtual void processInput(sf::Event& e);
    
    /**
     * \brief Called before destruct() when this entity is being removed from a level. Should probably delete
     * any raw pointers contained in the Entity here
     */
    virtual void despawn();
    
    /**
     * \brief Gets the level this entity is contained within
     * \return Pointer to the level
     */
    Level& getLevel() const;

    /**
     * \brief Gets the world this entity and its level are contained within
     * \return Pointer to the world
     */
    World* getWorld() const;

    AssetCache& getLevelAssetCache() const;
    MusicManager& getLevelMusicManager() const;

    /**
     * \brief Called every frame while this entity is colliding with any other amount of entities
     * \param otherEntities The vector of entities this entity is colliding with. This is the same as
     * m_collidingEntities, which can be got with getCollidingEntities()
     */
    virtual void onCollision(std::vector<Entity*>& otherEntities);
    /**
     * \brief Called the frame we start colliding with another entity
     * \param otherEntity The entity we have just started colliding with
     * \param otherBounds otherEntity's global bounds
     */
    virtual void onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds);
    /**
     * \brief Called the frame we stop colliding with another entity
     * \param otherEntity The entity we have just stopped colliding with
     * \param otherBounds otherEntity's global bounds
     */
    virtual void onEndCollision(Entity* otherEntity, const sf::FloatRect& otherBounds);

    bool m_colliding {false};
    Entity* m_lastCollidingEntity {nullptr};

    /**
     * \brief Gets all the entities this entity is currently colliding with
     * \return Vector of entities this entity is colliding with
     */
    const std::vector<Entity*>& getCollidingEntities() const;

private:
    /**
     * \brief Vector of entities we are currently colliding with
     */
    std::vector<Entity*> m_collidingEntities;

    /**
     * \brief Whether this entity is awaiting destruction at the end of this frame
     */
    bool m_pendingDestroy {false};
};

}
