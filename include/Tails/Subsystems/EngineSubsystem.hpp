#ifndef TAILS_ENGINESUBSYSTEM_HPP
#define TAILS_ENGINESUBSYSTEM_HPP

#include <Tails/Subsystems/Subsystem.hpp>

namespace tails
{
    class Engine;

    class EngineSubsystem : public Subsystem
    {
        friend Engine;

    public:
        virtual ~EngineSubsystem() = default;

        Engine& getEngine();
    };
}

#endif // TAILS_ENGINESUBSYSTEM_HPP
