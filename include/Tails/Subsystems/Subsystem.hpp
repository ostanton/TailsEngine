#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class Engine;

    // subsystems of Engine. A way for the engine to categorise and
    // branch off different tasks it does
    class TAILS_API Subsystem : public Object, public Tickable, public sf::Drawable
    {
        friend Engine;

    public:
        Engine& getEngine();

    protected:
        virtual void init(Engine& engine) {}
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
