#include "TailsEngine/Core/Screen.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include "TailsEngine/Core/ApplicationWindow.h"
#include "TailsEngine/Core/Viewport.h"

void tails::Screen::create()
{
    
}

void tails::Screen::display()
{
    
}

void tails::Screen::update(float deltaTime)
{
    
}

void tails::Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (size_t i {0}; i < widgets.size(); i++)
    {
        target.draw(*widgets[i]);
    }
}

void tails::Screen::remove()
{
    
}

void tails::Screen::destroy() const
{
    getViewport().destroyScreen(this);
}

tails::Viewport& tails::Screen::getViewport() const
{
    return *dynamic_cast<Viewport*>(outer);
}
