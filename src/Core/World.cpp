#include "TailsEngine/Core/World.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/GameInstance.h"

void tails::World::construct()
{
    Object::construct();

    loadLevel<Level>();
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

void tails::World::update(float deltaTime)
{
    if (onlyUpdateCurrentLevel && getCurrentLevel())
    {
        getCurrentLevel()->update(deltaTime);
        return;
    }

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
