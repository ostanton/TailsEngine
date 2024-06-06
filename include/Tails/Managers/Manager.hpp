#ifndef TAILS_MANAGER_HPP
#define TAILS_MANAGER_HPP

#include <Tails/Object.hpp>

namespace tails
{
    class EngineSubsystem;
    class ManagerSubsystem;

    class Manager : public Object
    {
        friend ManagerSubsystem;

    protected:
        virtual void added(EngineSubsystem& engineSubsystem) {} // called when added to the engine
        virtual void tick(float deltaTime) = 0;
        virtual void removed() {} // called when removed from the engine (on cleanup)
    };
}

#endif // TAILS_MANAGER_HPP
