#ifndef TAILS_TICKABLE_HPP
#define TAILS_TICKABLE_HPP

#include <Tails/Config.hpp>

namespace tails
{
    // abstract class that can tick, providing preTick and postTick methods also
    class TAILS_API Tickable
    {
    public:
        virtual ~Tickable() = default;

    protected:
        virtual void preTick() {}
        virtual void tick(float deltaTime) = 0;
        virtual void postTick() {}
    };
}

#endif // TAILS_TICKABLE_HPP
