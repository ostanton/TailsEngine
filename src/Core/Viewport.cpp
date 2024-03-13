#include "TailsEngine/Core/Viewport.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"

tails::Viewport::Viewport()
{
    
}

void tails::Viewport::create()
{
    
}

void tails::Viewport::processInput(sf::Event& e)
{
    for (const auto& screen : screens)
    {
        screen->processInput(e);
    }
}

void tails::Viewport::update()
{
    frameTime = clock.restart();

    for (const auto& screen : screens)
    {
        if (screen)
            screen->update(frameTime.asSeconds());
    }
}

void tails::Viewport::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& screen : screens)
    {
        target.draw(*screen);
    }
}

void tails::Viewport::setupData()
{
    for (auto& display : m_screensPendingDisplay)
    {
        display->display();
        screens.emplace_back(std::move(display));
    }

    m_screensPendingDisplay.clear();
    
    for (auto& screen : screens)
    {
        if (screen)
            screen->setupData();
    }
}

void tails::Viewport::cleanupData()
{
    for (auto& screen : screens)
    {
        if (screen)
        {
            screen->cleanupData();
            if (screen->m_pendingRemoval)
                destroyScreen(screen.get());
        }
    }
}

void tails::Viewport::displayScreen(Screen* screenToDisplay)
{
    m_screensPendingDisplay.emplace_back(screenToDisplay);
}

bool tails::Viewport::destroyScreen(const Screen* screenToDestroy)
{
    for (auto& screen : screens)
    {
        if (screen.get() == screenToDestroy)
        {
            screen->remove();
            screen.reset();
            screens.erase(std::find(screens.begin(), screens.end(), screen));
            return true;
        }
    }

    return false;
}

tails::Screen* tails::Viewport::getTopMostScreen() const
{
    if (screens.empty())
        return nullptr;
    
    return screens[0].get();
}

void tails::Viewport::setInputMode(InputMode inputMode) const
{
    getApplicationWindow()->targetInputMode = inputMode;
}
