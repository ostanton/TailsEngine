#ifndef TAILS_LAYER_HPP
#define TAILS_LAYER_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class State;
    class Engine;

    class TAILS_API Layer : public Object, public sf::Drawable, public Tickable
    {
        friend State;

    protected:
        virtual void init(State& state) {}
        virtual void added() {}
        virtual void removed() {}

        State& getState();
        Engine& getEngine();
    };
}

#endif // TAILS_LAYER_HPP
