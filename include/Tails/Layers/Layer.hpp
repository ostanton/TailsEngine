#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class State;

    class Layer : public Object, public sf::Drawable, public Tickable
    {
        friend State;

    protected:
        virtual void added(State& state) {}
        virtual void removed() {}
    };
}

#endif // TAILS_LAYER_HPP
