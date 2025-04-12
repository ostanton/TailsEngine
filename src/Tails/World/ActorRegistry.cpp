#include <Tails/World/ActorRegistry.hpp>
#include <Tails/String.hpp>
#include <Tails/World/Actor.hpp>

#include <unordered_map>
#include <iostream>

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
        if (getActorRegistryMap().find(name) != getActorRegistryMap().end())
            return getActorRegistryMap()[name]();

        return nullptr;
    }

    bool registerActorImpl(const CString& name, AllocateActorFunc allocFunc)
    {
        if (getActorRegistryMap().find(name) != getActorRegistryMap().end())
        {
            std::cout << "Actor Registry: Failed to register " << name << " actor, it already exists in the registry" << '\n';
            return false;
        }

        getActorRegistryMap().try_emplace(name, allocFunc);
        std::cout << "Actor Registry: Registered actor '" << name << "'\n";
        return true;
    }
}
