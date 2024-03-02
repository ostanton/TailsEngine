#pragma once
#include "TailsEngine/Core/Obj.h"
#include <SFML/Graphics/Sprite.hpp>

namespace tails
{
class MusicManager;
}

namespace tails
{
class AssetCache;
}

namespace sf
{
class Event;
}

namespace tails
{
class InputManager;
class ResourceManager;
class World;
class Level;
}

namespace tails
{
/**
 * \brief Base class for all entities. Every entity is a sprite. You do not need to do sprite things however,
 * or have any appearance at all. This might be changed for a more lax sf::Drawable instead of sf::Sprite,
 * like how the widgets work (if they do actually work that is, they might not). For now it is a sprite
 */
class Entity : public Object, public sf::Sprite
{
    friend World;
    friend Level;

public:
    /**
     * \brief Destroys this entity (deletes memory, etc.)
     */
    void destroy();

protected:
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

    virtual void onCollision(Entity* otherEntity, const sf::FloatRect& otherBounds);
    virtual void onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds);
    virtual void onEndCollision();

    bool m_colliding {false};
    Entity* m_lastCollidingEntity {nullptr};
};

}
