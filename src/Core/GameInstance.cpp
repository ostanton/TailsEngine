#include "TailsEngine/Core/GameInstance.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include <TailsEngine/Core/World.h>
#include "TailsEngine/Core/ApplicationWindow.h"

tails::GameInstance::GameInstance()
{
    
}

void tails::GameInstance::construct()
{
    Object::construct();

    world.reset(newObject<World>(this));
}

void tails::GameInstance::pauseGame(bool pause)
{
    m_gamePaused = pause;
}

bool tails::GameInstance::isGamePaused() const
{
    return m_gamePaused;
}

tails::Viewport& tails::GameInstance::getViewport() const
{
    return *getApplicationWindow()->viewport;
}

void tails::GameInstance::create()
{
    world->create();
}

void tails::GameInstance::processInput(sf::Event& e)
{
    world->processInput(e);
}

void tails::GameInstance::update()
{
    const sf::Time gameTimer {clock.restart()};

    if (!m_gamePaused)
    {
        world->update(gameTimer.asSeconds());
    }
}

void tails::GameInstance::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*world);
}

void tails::GameInstance::setupData()
{
    world->setupData();
}

void tails::GameInstance::cleanupData()
{
    world->cleanupData();
}
