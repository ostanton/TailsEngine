#include <Tails/World/ActorRegistry.hpp>
#include <Tails/String.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/Log.hpp>

#include <unordered_map>

namespace tails::impl
{
    using ActorRegistryMap = std::unordered_map<CString, AllocateActorFunc>;
    
    ActorRegistryMap& getActorRegistryMap()
    {
        static ActorRegistryMap actorRegistry;
        return actorRegistry;
    }
    
    std::unique_ptr<CActor> allocateActor(const CString& name)
    {
        if (getActorRegistryMap().contains(name))
            return getActorRegistryMap()[name]();

        return nullptr;
    }

    bool registerActorImpl(const CString& name, AllocateActorFunc allocFunc)
    {
        if (getActorRegistryMap().contains(name))
        {
            TAILS_LOG_VA(ActorRegistry, Error,
                "Failed to register '%s', it already exists in the registry", name.getData());
            return false;
        }

        getActorRegistryMap().try_emplace(name, allocFunc);
        TAILS_LOG_VA(ActorRegistry, Message, "Registered '%s'", name.getData());
        return true;
    }
}
