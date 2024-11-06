#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Object.hpp>
#include <Tails/Tickable.hpp>

#include <SFML/Graphics/Drawable.hpp>

namespace tails
{
    class CEngine;
    
    class TAILS_API CSubsystem : public CObject, public ITickable, public sf::Drawable
    {
        friend CEngine;

    public:
        [[nodiscard]] CEngine& getEngine() const noexcept;
        
    protected:
        /**
         * Called when the engine initialises the registered subsystems
         */
        virtual void init() = 0;
    };
}

#endif // TAILS_SUBSYSTEM_HPP
