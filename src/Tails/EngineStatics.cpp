#include <Tails/EngineStatics.hpp>
#include <Tails/Engine.hpp>

namespace tails
{
    Engine* EngineStatics::getEngine(const Object* object)
    {
        return object->getTypedOuter<Engine>();
    }

    const Paths* EngineStatics::getPaths(const Object* object)
    {
        return &getEngine(object)->getFilePaths();
    }

    float EngineStatics::getEngineDeltaTime(const Object* object)
    {
        return getEngine(object)->getDeltaTime();
    }
} // tails
