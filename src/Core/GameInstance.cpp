#include "TailsEngine/Core/GameInstance.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <TailsEngine/Core/World.h>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Managers/ResourceManager.h"

tails::GameInstance::GameInstance()
{
    gameView.reset(new sf::View);
    clock.reset(new sf::Clock);
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
    const sf::Time gameTimer {clock->restart()};

    if (!m_gamePaused)
    {
        world->update(gameTimer.asSeconds());
    }
}

void tails::GameInstance::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*world);
}
