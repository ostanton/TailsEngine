#include <Tails/EngineRegistry.hpp>

#include <Tails/Entity.hpp>

namespace tails
{
    CEngineRegistry::CEngineRegistry()
    {
        registerClass<CEntity>("Entity");
    }
}
