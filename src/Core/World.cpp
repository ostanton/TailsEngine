#include "TailsEngine/Core/World.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/GameInstance.h"

void tails::World::construct()
{
    Object::construct();

    createAndOpenLevel<Level>();
}

void tails::World::create()
{
    // TODO - Level's outer is null at this point??
    getCurrentLevel()->create();
}

tails::ResourceManager& tails::World::getResourceManager() const
{
    return dynamic_cast<GameInstance*>(outer)->getResourceManager();
}

tails::InputManager& tails::World::getInputManager() const
{
    return dynamic_cast<GameInstance*>(outer)->getInputManager();
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
}

void tails::World::update(float deltaTime)
{
    currentLevel->update(deltaTime);
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
