#ifndef TAILS_TICKABLE_HPP
#define TAILS_TICKABLE_HPP

#include <Tails/Config.hpp>

namespace tails
{
    class TAILS_API ITickable
    {
    public:
        virtual ~ITickable() = default;
        
    protected:
        /**
         * Used for any "deferred" creation of objects.
         */
        virtual void preTick() {}

        /**
         * Called every frame, used for checking inputs, etc., anything
         * that should happen within a frame basically.
         * @param deltaTime Length of the previous frame
         */
        virtual void tick(float deltaTime) = 0;

        /**
         * Simulates a garbage collector. Destroys any objects or memory that are pending destroy.
         */
        virtual void postTick() {}
    };
}

#endif // TAILS_TICKABLE_HPP
