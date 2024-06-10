#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    Engine& Subsystem::getEngine()
    {
        return *getTypedOuter<Engine>();
    }
}
