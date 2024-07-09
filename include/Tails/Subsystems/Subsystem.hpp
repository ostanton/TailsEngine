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
        /**
         * Called once this subsystem is initialised. Other subsystems may not yet be initialised, so do not
         * rely on them here. Do that in postInit().
         * @param engine The engine instance
         */
        virtual void init(Engine& engine) {}
        /**
         * Called once all subsystems are initialised, it is safe to access other subsystems here.
         */
        virtual void postInit() {}
        /**
         * Called once this subsystem is deinitialised. Other subsystems are still valid here.
         */
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
