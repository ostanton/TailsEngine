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
    
    /**
     * Abstract base class for all widgets.
     * 
     * A widget has no transform by itself (aside from its additive transform). Its actual screen position, etc.
     * are dictated by the slot it currently resides in. If it is in no slot, it has no transform.
     *
     * A widget's outer is the panel widget it resides in, not its slot. It has m_slot for that
     */
    class TAILS_API CWidget :
        public CObject,
        public ITickable,
        public sf::Drawable
    {
        friend CPanel;
        friend CSlot;
        
    public:
        [[nodiscard]] CEngine& getEngine() const;
        [[nodiscard]] CPanel* getParent() const;
        [[nodiscard]] CSlot* getSlot() const;
        
        void destroy();

        [[nodiscard]] sf::Vector2f getPosition() const;
        [[nodiscard]] sf::Angle getRotation() const;
        [[nodiscard]] sf::Vector2f getScale() const;
        [[nodiscard]] std::optional<std::reference_wrapper<const sf::Transform>> getTransform() const;
        [[nodiscard]] std::optional<std::reference_wrapper<const sf::Transform>> getInverseTransform() const;

        [[nodiscard]] virtual sf::FloatRect getLocalBounds() const;

        /**
         * Additive transform for this widget
         */
        sf::Transform transform;
        
    protected:
        /**
         * The window input event
         * @param ev SFML window event
         * @return Whether to let this event continue down the tree and to child widgets
         */
        virtual bool inputEvent(const sf::Event& ev) {return true;}

    private:
        CSlot* m_slot {nullptr};
    };
}

#endif // TAILS_UI_WIDGET_HPP
