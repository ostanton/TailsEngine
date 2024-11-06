#include <Tails/Subsystem.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    CEngine& CSubsystem::getEngine() const noexcept
    {
        return *getTypedOuter<CEngine>();
    }
}
