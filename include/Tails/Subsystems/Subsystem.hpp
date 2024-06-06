#ifndef TAILS_SUBSYSTEM_HPP
#define TAILS_SUBSYSTEM_HPP

#include <Tails/Object.hpp>

namespace tails
{
    class Subsystem : public Object
    {
    protected:
        virtual void init() = 0;
        virtual void preTick() {}
        virtual void tick(float deltaTime) {}
        virtual void postTick() {}
        virtual void deinit() {}
    };
}

#endif // TAILS_SUBSYSTEM_HPP
