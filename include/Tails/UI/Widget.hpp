#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Object.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails
{
    class Slot;

    // the outer of a widget is the Screen that owns it
    class Widget : public Object, public sf::Drawable, public sf::Transformable
    {
        friend Slot;

    public:
        Slot* slot; // the slot that owns this widget

    protected:
        virtual void tick(float deltaTime) {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif // TAILS_WIDGET_HPP
