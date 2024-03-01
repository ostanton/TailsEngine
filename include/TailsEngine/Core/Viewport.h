#pragma once
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include "Obj.h"
#include "TailsEngine/Widgets/Widget.h"

namespace tails
{
class ApplicationWindow;
class Widget;
}

namespace sf
{
class Clock;
class View;
}

namespace tails
{
/**
 * \brief This handles widgets and UI through its own sf::View, handled via the tails::ApplicationWindow
 */
class Viewport : public Object, public sf::Drawable
{
    friend ApplicationWindow;
    
public:
    Viewport();

    unique_ptr<sf::Clock> clock;
    sf::Time frameTime;

protected:
    /**
     * \brief Called in postInitialise of ApplicationWindow
     */
    void create();
    virtual void update();
    void updateWidgets(const std::vector<unique_ptr<sf::Drawable>>& inWidgets);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    unique_ptr<sf::View> widgetView;

    // TODO - Abstract this into WidgetTree class?

    template<typename WidgetT>
    WidgetT createWidget(Widget* parent = nullptr)
    {
        sf::Drawable* drawable { newObject<WidgetT>(this) };
        Widget* resultWidget { dynamic_cast<Widget*>(drawable) };
        
        if (parent && resultWidget)
        {
            parent->addChild(drawable);
            resultWidget->parent = parent;
        }
        else
        {
            widgets.emplace_back(drawable);
        }

        return dynamic_cast<WidgetT*>(drawable);
    }
    
    /**
     * \brief The list of widgets to update and draw, etc.
     * There is not one root widget, as any number of widgets can be added here to just be drawn
     * without having a parent-child hierarchy
     */
    std::vector<unique_ptr<sf::Drawable>> widgets;
};

}
