#include "TailsEngine/Core/Viewport.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Managers/ResourceManager.h"

tails::Viewport::Viewport()
{
    widgetView.reset(new sf::View);
    clock.reset(new sf::Clock);
}

void tails::Viewport::create()
{
    createAndDisplayScreen<Screen>();
}

void tails::Viewport::update()
{
    frameTime = clock->restart();

    for (const auto& screen : screens)
    {
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

void tails::Viewport::displayScreen(Screen* screenToDisplay)
{
    screens.emplace_back(screenToDisplay);
    screenToDisplay->display();
}

bool tails::Viewport::destroyScreen(const Screen* screenToDestroy)
{
    auto screensVec = getScreensRaw();
    
    if (std::find(screensVec.begin(), screensVec.end(), screenToDestroy) == screensVec.end())
        return false;

    screensVec.erase(std::find(screensVec.begin(), screensVec.end(), screenToDestroy));

    screens.clear();
    
    for (auto screen : screensVec)
    {
        screens.emplace_back(screen);
    }
    
    return true;
}

std::vector<tails::Screen*> tails::Viewport::getScreensRaw() const
{
    std::vector<Screen*> resultVector;
    // Pre-allocate size so it doesn't need to in the for loop
    resultVector.reserve(screens.size());
    
    for (auto& screen : screens)
    {
        resultVector.emplace_back(screen.get());
    }

    return resultVector;
}

tails::Screen* tails::Viewport::getTopMostScreen() const
{
    if (screens.empty())
        return nullptr;
    
    return screens[0].get();
}
