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

void tails::World::openTargetLevel()
{
    if (!m_levelToOpen)
        return;
    
    if (currentLevel)
    {
        for (auto& createdEntity : currentLevel->m_entities)
        {
            currentLevel->destroyEntity(createdEntity);
        }
    }

    currentLevel = std::move(m_levelToOpen);
    m_levelToOpen.reset();
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
    target.draw(*getCurrentLevel());
}

void tails::World::setupData()
{
    currentLevel->setupData();
}

void tails::World::cleanupData()
{
    currentLevel->cleanupData();

    openTargetLevel();
}

tails::Level* tails::World::getCurrentLevel() const
{
    return currentLevel.get();
}

tails::GameInstance& tails::World::getGameInstance() const
{
    return *dynamic_cast<GameInstance*>(outer);
}

tails::Viewport& tails::World::getViewport() const
{
    return getGameInstance().getViewport();
}

void tails::World::setViewCameraPosition(const sf::Vector2f& position) const
{
    getGameInstance().gameView.setCenter(position);
}
