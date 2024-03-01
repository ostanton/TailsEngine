#include "TailsEngine/Core/World.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/GameInstance.h"
#include "TailsEngine/Debug/Debug.h"

void tails::World::construct()
{
    Object::construct();

    currentLevel.reset(newObject<Level>(this));
}

void tails::World::create()
{
    currentLevel->create();
}

bool tails::World::destroyEntity(const Entity* entityToDestroy) const
{
    for (auto& entity : currentLevel->entities)
    {
        if (entity.get() == entityToDestroy)
        {
            entity->despawn();
            entity.reset();
            currentLevel->entities.erase(std::find(
                currentLevel->entities.begin(), currentLevel->entities.end(), entity));
            return true;
        }
    }

    return false;
}

void tails::World::openLevel(Level* levelToOpen)
{
    if (currentLevel)
    {
        // Call any methods on entities, etc. before resetting the pointer
        for (const auto& entity : currentLevel->entities)
        {
            entity->despawn();
        }
    }
    
    currentLevel.reset(levelToOpen);
    currentLevel->create();
}

void tails::World::update(float deltaTime)
{
    currentLevel->update(deltaTime);
}

void tails::World::processInput(sf::Event& e)
{
    currentLevel->processInput(e);
}

void tails::World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (getCurrentLevel())
        target.draw(*getCurrentLevel());
}

tails::Level* tails::World::getCurrentLevel() const
{
    return currentLevel.get();
}
