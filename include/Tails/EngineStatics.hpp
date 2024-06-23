#ifndef TAILS_ENGINESTATICS_HPP
#define TAILS_ENGINESTATICS_HPP

#include <Tails/Config.hpp>

namespace tails
{
    struct Paths;
    class Subsystem;
    class Object;
    class Engine;

    class TAILS_API EngineStatics
    {
    public:
        /**
         * Gets the game's engine by traversing the outers of this object
         * @param object Object of which outers will be traversed
         * @return The engine, if found
         */
        static Engine* getEngine(const Object* object);
        static const Paths* getPaths(const Object* object);
    };

} // tails

#endif //TAILS_ENGINESTATICS_HPP
