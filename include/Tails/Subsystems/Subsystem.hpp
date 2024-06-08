#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

namespace sf
{
    class RenderTarget;
}

namespace tails
{
    class Engine;

    // subsystems of Engine. A way for the engine to categorise and
    // branch off different tasks it does
    class Subsystem : public Object, public Tickable
    {
        friend Engine;

    protected:
        virtual void init(Engine& engine) = 0;
        virtual void draw(sf::RenderTarget& target) {}
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
