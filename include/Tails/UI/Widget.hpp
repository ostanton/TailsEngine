#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>
#include <Tails/Events/MultiEvent.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails
{
    class Slot;
    class PanelWidget;
    class ScreenLayer;

    // the outer of a widget is the Screen that owns it
    class TAILS_API Widget : public Object, public sf::Drawable, public sf::Transformable, public Tickable
    {
        friend Slot;
        friend ScreenLayer;

    public:
        Slot* slot; // the slot that owns this widget

        void removeFromParent();
        PanelWidget* getParent() const;

        // size-setting methods for child widgets that wrap SFML classes (shapes, sprite, etc.) to override and
        // provide specific functionality for layouts
        inline void setSize(float w, float h) {m_size.x = w; m_size.y = h; setSize(m_size);}
        inline virtual void setSize(const sf::Vector2f& size) {m_size = size;}
        inline virtual const sf::Vector2f& getSize() {return m_size;}

        /* Focus */

        // set focus to this widget
        void setFocus();
        inline MultiEvent<Widget*>& getFocusEvent() {return m_onFocus;}
        inline MultiEvent<Widget*>& getUnFocusEvent() {return m_onUnFocus;}
        // check if this widget is currently focused
        bool isFocused();

    protected:
        sf::Vector2f m_size;

    private:
        MultiEvent<Widget*> m_onFocus;
        MultiEvent<Widget*> m_onUnFocus;
    };
}

#endif // TAILS_WIDGET_HPP
