#ifndef TAILS_ENGINEREGISTRY_HPP
#define TAILS_ENGINEREGISTRY_HPP

#include <Tails/Config.hpp>
#include <Tails/ClassRegistry.hpp>

namespace tails
{
    /**
     * Registers all engine types that should be serialisable.
     */
    class TAILS_API CEngineRegistry : public CClassRegistry
    {
    public:
        CEngineRegistry();
    };
}

#endif // TAILS_ENGINEREGISTRY_HPP
