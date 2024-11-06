#ifndef TAILS_UI_WIDGET_HPP
#define TAILS_UI_WIDGET_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transform.hpp>

namespace sf
{
    class Event;
}

namespace tails
{
    class CEngine;
}

namespace tails::ui
{
    class CSlot;
    class CPanel;
    class CUISubsystem;
    
    /**
     * Base class for all widgets.
     * 
     * TODO - either have private parent Transformable class, or find a way to get a widget's location to then
     * be used by the next panel's child's slot for an offset. Because how would it offset otherwise?? I think it
     * should be inherited, as then the widget can provide its own bounds, the transform set by its slot, and
     * the additive transform on top of that. It won't know about its slot-set bounds otherwise
     * (unless set some other way)
     */
    class TAILS_API CWidget :
        public CObject,
        public ITickable,
        public sf::Drawable
    {
        friend CPanel;
        friend CUISubsystem;
        
    public:
        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CPanel* getParent() const;
        [[nodiscard]] CSlot* getSlot() const;
        
        void destroy();

        /**
         * Additive transform for this widget
         */
        sf::Transform transform;
        
    protected:
        /**
         * The window input event
         * @param ev SFML window event
         */
        virtual void eventInput(const sf::Event& ev) {}
    };
}

#endif // TAILS_UI_WIDGET_HPP
