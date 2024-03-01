#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

#include "Level.h"
#include "Obj.h"
#include "TailsEngine/Level/Entity.h"

namespace tails
{
class InputManager;
class GameInstance;
}

namespace tails
{
/**
 * \brief A class to easily switch between level classes and spawn entities. This isn't strictly needed,
 * but helps to segment things.
 */
class World : public Object, public sf::Drawable
{
    friend GameInstance;
    
public:
    void construct() override;
    void create();

    // TODO - destroy entities
    
    /**
    * \brief Spawns an entity in the current level. Do not use if you want to create an Entity before a
     * level is loaded
     * \tparam EntityT Entity type, should derive from Entity
     * \return Entity object pointer
     */
    template<typename EntityT>
    EntityT* spawnEntity()
    {
        return spawnEntity<EntityT>(getCurrentLevel());
    }

    /**
     * \brief Spawns an entity in the specified target level. Do not use if you want to create an Entity before a
     * level is loaded
     * \tparam EntityT Entity type, should derive from Entity
     * \param targetLevel The level of which to spawn the entity in
     * \return Entity object pointer
     */
    template<typename EntityT>
    EntityT* spawnEntity(Level* targetLevel)
    {
        if (!targetLevel)
            return nullptr;
        
        Entity* resultEntity { newObject<EntityT>(targetLevel) };

        targetLevel->entities.emplace_back(resultEntity);
        resultEntity->spawn();

        return dynamic_cast<EntityT*>(resultEntity);
    }

    /**
     * \brief The currently loaded level
     */
    unique_ptr<Level> currentLevel;

    /**
     * \brief Gets the current level (that is "in play")
     * \return Pointer to the level
     */
    Level* getCurrentLevel() const;

    /**
     * \brief Creates a level object and loads it into the levels vector
     * \tparam LevelT The level type to load
     * \return Pointer to the created level object
     */
    template<typename LevelT>
    LevelT* createAndOpenLevel()
    {
        auto resultLevel = createLevel<LevelT>();
        openLevel(resultLevel);

        return dynamic_cast<LevelT*>(resultLevel);
    }
    // TODO - overloaded loadLevel methods with specific inputs for things?
    // Could have a .json ldtk file input, so we don't even need subclasses?

    void openLevel(Level* levelToOpen);

    /**
     * \brief Should favour createAndOpenLevel unless you need to setup things beforehand. createAndOpenLevel
     * stores the created pointer into a smart pointer immediately. This uses no smart pointer. It is your
     * responsibility to prevent leaks
     * \tparam LevelT The level type to create
     * \return Pointer to the created level object
     */
    template<typename LevelT>
    LevelT* createLevel()
    {
        Level* resultLevel { newObject<LevelT>(this) };

        return dynamic_cast<LevelT*>(resultLevel);
    }

protected:
    /**
     * \brief Called every frame
     * \param deltaTime Time since last frame
     */
    virtual void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    /**
     * \brief Method for creating entities but not "spawning" them, so the level can spawn them once its create()
     * method is called. This should be used instead of spawnEntity whenever the level is not loaded
     * \tparam EntityT The entity type
     * \return Pointer to entity object
     */
    template<typename EntityT>
    EntityT* createEntity(Level* targetLevel)
    {
        if (!targetLevel)
            return nullptr;
        
        Entity* resultEntity { newObject<EntityT>(targetLevel) };

        targetLevel->entities.emplace_back(resultEntity);
        // Only emplace_back, do not spawn. The level spawns in its create() method

        return dynamic_cast<EntityT*>(resultEntity);
    }
};

}
