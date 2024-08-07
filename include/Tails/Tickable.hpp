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
        virtual void preTick() {}
        virtual void tick(float deltaTime) = 0;
        virtual void postTick() {}
    };
}

#endif // TAILS_TICKABLE_HPP
