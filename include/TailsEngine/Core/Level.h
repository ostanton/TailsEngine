#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

#include "Obj.h"

namespace tails
{
class Entity;
class World;
}

namespace tails
{
/**
 * \brief A class that holds a vector of entities, and generally shouldn't have specialised subclasses.
 * Each level can either be a subclass of this class, with its own rules, etc., or an object of this class
 * with whatever members set from the World's load level method (TODO whatever that'll be)
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
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

}
