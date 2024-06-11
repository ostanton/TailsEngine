#ifndef TAILS_ENGINESTATICS_HPP
#define TAILS_ENGINESTATICS_HPP

namespace tails
{
    struct Paths;
    class Subsystem;
    class Object;

    class EngineStatics
    {
    public:
        static const Paths& getPaths(const Subsystem* subsystem);
        static const Paths* getPaths(const Object* object);
    };

} // tails

#endif //TAILS_ENGINESTATICS_HPP
