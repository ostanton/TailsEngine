#include <Tails/Subsystems/EngineSubsystem.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    Engine& EngineSubsystem::getEngine()
    {
        return *getTypedOuter<Engine>();
    }
}
