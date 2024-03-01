#include "TailsEngine/Core/Level.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Level/CollisionTest.h"
#include "TailsEngine/Level/TailsEntity.h"

void tails::Level::construct()
{
    Object::construct();

    // loop entities in .json and create them ready for create() to spawn them
    getWorld()->spawnEntity<TailsEntity>(this);
    getWorld()->spawnEntity<CollisionTest>(this);
}

tails::World* tails::Level::getWorld() const
{
    return dynamic_cast<World*>(outer);
}

void tails::Level::create()
{
    // "spawn" every entity
    for (size_t i {0}; i < entities.size(); i++)
    {
        entities[i]->spawn();
    }
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
    for (size_t i {0}; i < entities.size(); i++)
    {
        if (entities[i])
            entities[i]->processInput(e);
    }
}

void tails::Level::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < entities.size(); i++)
    {
        target.draw(*entities[i]);
    }
}
