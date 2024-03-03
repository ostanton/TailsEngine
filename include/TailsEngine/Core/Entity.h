#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "TailsEngine/Core/Obj.h"

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
class Viewport;
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
class Entity : public Object, public sf::Drawable, public sf::Transformable
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

    /**
     * \brief Called before update(). Generally where inputs should go (not a hard rule). Can access sf::RenderWindow's
     * sf::Event events from e
     * \param e Window event from ApplicationWindow
     */
    virtual void processInput(sf::Event& e);

    /**
     * \brief Called every frame after processInput() and update(). This is where you should components are drawn.
     * We multiply our own transform with the states parameter's to have a world transform. Then each component's
     * own transform is local to it
     * \param target The RenderTarget to draw components to
     * \param states RenderStates dictating how components should be drawn
     */
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
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
    World& getWorld() const;

    AssetCache& getLevelAssetCache() const;
    MusicManager& getLevelMusicManager() const;

    Viewport& getViewport() const;

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

    ///// TESTING COMPONENT SYSTEM /////
    /*
     * This would be used instead of the Entity inheriting directly from sf::Sprite. The idea here is to use
     * SFML's classes as components, like the primitive components in Unreal's Actors (Static Mesh Component, etc.).
     * They have no logic, their purpose is to provide visuals or bounding boxes for the Entity
     */

    /**
     * \brief Creates a component and adds it to the m_components vector
     * \tparam CompT Component type to create (must inherit sf::Drawable)
     * \return Pointer to created component
     */
    template<typename CompT>
    CompT* createComponent()
    {
        static_assert(std::is_base_of_v<Drawable, CompT>, "Cannot create component not of type sf::Drawable");
        
        Drawable* resultComponent { new CompT };

        m_components.emplace_back(resultComponent);

        return dynamic_cast<CompT*>(resultComponent);
    }

    /**
     * \brief Destroys a component and removes it from the m_components vector. Any pointer to this now is invalid
     * \param componentToDestroy Component object to destroy
     * \return Whether destruction was successful
     */
    bool destroyComponent(Drawable* componentToDestroy)
    {
        const auto iter = std::find_if(
            m_components.begin(), m_components.end(),
            [componentToDestroy] (const unique_ptr<Drawable>& component)
            {
                return component.get() == componentToDestroy;
            });
        
        if (iter != m_components.end())
        {
            m_components.erase(iter);
            return true;
        }

        return false;
    }

    /**
     * \brief Finds a component of specified type in the m_components vector. Returns nullptr if none were found
     * \tparam CompT Component type to find
     * \return Pointer to found component, or nullptr if one couldn't be found
     */
    template<typename CompT>
    CompT* findComponent() const
    {
        static_assert(std::is_base_of_v<Drawable, CompT>, "Cannot find component not of type sf::Drawable");
        
        for (auto& component : m_components)
        {
            if (std::is_same_v<decltype(component.get()), CompT>)
            {
                return dynamic_cast<CompT*>(component.get());
            }
        }

        return nullptr;
    }

private:
    /**
     * \brief Vector of entities we are currently colliding with
     */
    std::vector<Entity*> m_collidingEntities;

    /**
     * \brief Testing components system
     */
    std::vector<unique_ptr<Drawable>> m_components;

    /**
     * \brief Whether this entity is awaiting destruction at the end of this frame
     */
    bool m_pendingDestroy {false};
};

}
