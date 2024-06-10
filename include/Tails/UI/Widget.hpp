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
    class ScreenLayer;

    // the outer of a widget is the Screen that owns it
    class Widget : public Object, public sf::Drawable, public sf::Transformable, public Tickable
    {
        friend Slot;
        friend ScreenLayer;

    public:
        Slot* slot; // the slot that owns this widget

        void removeFromParent();
        PanelWidget* getParent();

        // size-setting methods for child widgets that wrap SFML classes (shapes, sprite, etc.) to override and provide specific functionality for layouts
        void setSize(float w, float h) {m_size.x = w; m_size.y = h; setSize(m_size);}
        virtual void setSize(const sf::Vector2f& size) {m_size = size;}
        virtual const sf::Vector2f& getSize() {return m_size;}

    protected:
        sf::Vector2f m_size;
    };
}

#endif // TAILS_WIDGET_HPP
