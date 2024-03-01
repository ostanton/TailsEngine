#include "TailsEngine/Core/Viewport.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>

#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Widgets/Widget.h"

tails::Viewport::Viewport()
{
    widgetView.reset(new sf::View);
    clock.reset(new sf::Clock);
}

void tails::Viewport::create()
{
    
}

void tails::Viewport::update()
{
    // Create an sf::Time object to store the time since last frame
    frameTime = clock->restart();
    
    updateWidgets(widgets);
}

void tails::Viewport::updateWidgets(const std::vector<unique_ptr<sf::Drawable>>& inWidgets)
{
    // Recursively iterate through widgets and update them
    for (size_t i {0}; i < inWidgets.size(); i++)
    {
        Widget* widget { dynamic_cast<Widget*>(inWidgets[i].get()) };
        widget->update(frameTime.asSeconds());
        updateWidgets(widget->children);
    }
}

void tails::Viewport::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Iterate through widgets and draw them to the render target
    for (size_t i {0}; i < widgets.size(); i++)
    {
        if (const auto drawable = dynamic_cast<sf::Drawable*>(widgets[i].get()))
            target.draw(*drawable);
        else
        {
            tails::Debug::log("Viewport::draw - Widget failed to cast to sf::Drawable");
        }
    }
}
