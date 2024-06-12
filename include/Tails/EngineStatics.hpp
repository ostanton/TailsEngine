#ifndef TAILS_ENGINESTATICS_HPP
#define TAILS_ENGINESTATICS_HPP

#include <Tails/Config.hpp>

namespace tails
{
    struct Paths;
    class Subsystem;
    class Object;

    class TAILS_API EngineStatics
    {
    public:
        static const Paths& getPaths(const Subsystem* subsystem);
        static const Paths* getPaths(const Object* object);
    };

} // tails

#endif //TAILS_ENGINESTATICS_HPP
