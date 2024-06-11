#include <Tails/EngineStatics.hpp>
#include <Tails/Engine.hpp>
#include <Tails/Subsystems/Subsystem.hpp>

namespace tails
{
    const Paths& EngineStatics::getPaths(const Subsystem* subsystem)
    {
        return subsystem->getTypedOuter<Engine>()->getFilePaths();
    }

    const Paths* EngineStatics::getPaths(const Object* object)
    {
        Object* pOuter {object->outer};

        // loop outers until it is no longer valid, or until we find the engine
        while (pOuter)
        {
            if (auto engine = dynamic_cast<Engine*>(pOuter))
            {
                return &engine->getFilePaths();
            }
        }

        return nullptr;
    }
} // tails
