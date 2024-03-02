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

bool tails::World::destroyEntity(Entity* entityToDestroy) const
{
    /*
    for (auto& entity : currentLevel->entities)
    {
        if (entity.get() == entityToDestroy)
        {
            entity->despawn();
            // Do not need to reset() entity, as it is a unique pointer, and it is deleted with erase() anyway
            currentLevel->entities.erase(std::find(
                currentLevel->entities.begin(), currentLevel->entities.end(), entity));
            return true;
        }
    }*/

    entityToDestroy->despawn();

    const auto iter = std::find_if(
        currentLevel->entities.begin(), currentLevel->entities.end(),
        [entityToDestroy] (const unique_ptr<Entity>& entity)
    {
        return entity.get() == entityToDestroy;
    });

    currentLevel->entities.erase(iter);

    return false;
}

void tails::World::openLevel(Level* levelToOpen)
{
    if (!currentLevel)
    {
        currentLevel.reset(levelToOpen);
        currentLevel->create();
        return;
    }
    
    if (currentLevel->entities.empty())
    {
        Debug::log("No entities to destroy");
        currentLevel.reset(levelToOpen);
        currentLevel->create();
        return;
    }
    
    size_t index {0};

    for (index = 0; index < currentLevel->entities.size(); index++)
    {
        currentLevel->entities[index]->despawn();
        currentLevel->entities.erase(std::find(
            currentLevel->entities.begin(), currentLevel->entities.end(),
            currentLevel->entities[index]));
        index--;
    }

    // Call any methods on entities, etc. before erasing them
    /*
    for (auto& entity : currentLevel->entities)
    {
        // Despawn all the entities before loading new level
        entity->despawn();
        currentLevel->entities.erase(std::find(
            currentLevel->entities.begin(), currentLevel->entities.end(), entity));
    }*/

    currentLevel.reset(levelToOpen);
    currentLevel->create();
}

void tails::World::update(float deltaTime)
{
    if (currentLevel->isReady())
        currentLevel->update(deltaTime);
}

void tails::World::processInput(sf::Event& e)
{
    if (currentLevel->isReady())
        currentLevel->processInput(e);
}

void tails::World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (getCurrentLevel() && currentLevel->isReady())
        target.draw(*getCurrentLevel());
}

tails::Level* tails::World::getCurrentLevel() const
{
    return currentLevel.get();
}
