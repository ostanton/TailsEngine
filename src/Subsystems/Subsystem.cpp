#include <Tails/Subsystems/Subsystem.cpp>
#include <Tails/Engine.hpp>

namespace tails
{
    Engine& getEngine()
    {
        return *getTypedOuter<Engine>();
    }
}
