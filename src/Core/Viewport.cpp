#include "TailsEngine/Core/Viewport.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Core/TestScreen.h"

tails::Viewport::Viewport()
{
    widgetView.reset(new sf::View);
    clock.reset(new sf::Clock);
}

void tails::Viewport::create()
{
    createAndDisplayScreen<TestScreen>();
}

void tails::Viewport::update()
{
    frameTime = clock->restart();

    // TODO - Might need to remake so it can account for destroyed screens
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

void tails::Viewport::cleanupData()
{
    for (auto& screen : screens)
    {
        if (screen)
            screen->cleanupData();
    }
}

void tails::Viewport::displayScreen(Screen* screenToDisplay)
{
    screens.emplace_back(screenToDisplay);
    screenToDisplay->display();
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
