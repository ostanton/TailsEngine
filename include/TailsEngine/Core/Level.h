#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

#include "Obj.h"

namespace sf
{
class Event;
}

namespace tails
{
class Entity;
class World;
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
    
protected:
    /**
     * \brief Called when this level is created and its members should all be initialised
     */
    virtual void create();
    /**
     * \brief Called every frame this level is alive
     * \param deltaTime Time since last frame
     */
    virtual void update(float deltaTime);
    virtual void processInput(sf::Event& e);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
