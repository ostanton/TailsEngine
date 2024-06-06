#include <Tails/Subsystems/EngineSubsystem.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    Engine& getEngine()
    {
        return *getTypedOuter<Engine>();
    }
}
