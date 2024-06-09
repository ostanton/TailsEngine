#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails
{
    class Slot;
    class PanelWidget;

    // the outer of a widget is the Screen that owns it
    class Widget : public Object, public sf::Drawable, sf::Transformable, public Tickable
    {
        friend Slot;

    public:
        Slot* slot; // the slot that owns this widget

        void removeFromParent();
        PanelWidget* getParent();
    };
}

#endif // TAILS_WIDGET_HPP
