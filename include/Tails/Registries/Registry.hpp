#ifndef TAILS_REGISTRY_HPP
#define TAILS_REGISTRY_HPP

namespace tails
{
    class Engine;

    // abstract base class for registries
    class Registry
    {
    protected:
        virtual void init(Engine& engine) = 0;
    };
}

#endif // TAILS_REGISTRY_HPP
