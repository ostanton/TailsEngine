#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class Engine;

    // subsystems of Engine. A way for the engine to categorise and
    // branch off different tasks it does
    class Subsystem : public Object, public Tickable, public sf::Drawable
    {
        friend Engine;

    protected:
        virtual void init(Engine& engine) {}
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
