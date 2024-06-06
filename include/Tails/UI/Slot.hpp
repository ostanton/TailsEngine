#ifndef TAILS_WIDGETSLOT_HPP
#define TAILS_WIDGETSLOT_HPP

#include <Tails/Object.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class Widget;

    class Slot : public Object, public sf::Drawable
    {
    public:
        Widget* parent {nullptr};
        Widget* content {nullptr};

    protected:
        virtual void tick(float deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    };
}

#endif // TAILS_WIDGETSLOT_HPP
