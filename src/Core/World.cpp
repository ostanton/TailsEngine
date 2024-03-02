#include "TailsEngine/Core/World.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/GameInstance.h"

void tails::World::construct()
{
    Object::construct();

    currentLevel.reset(newObject<Level>(this));
}

void tails::World::create()
{
    currentLevel->create();
}

void tails::World::openLevel(Level* levelToOpen)
{
    if (currentLevel)
    {
        for (auto& createdEntity : currentLevel->m_createdEntities)
        {
            currentLevel->destroyEntity(createdEntity.get());
        }
    }

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
