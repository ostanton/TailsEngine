#ifndef TAILS_ACTOR_REGISTRY_HPP
#define TAILS_ACTOR_REGISTRY_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class CActor;
    class CString;

    namespace impl
    {
        using AllocateActorFunc = std::unique_ptr<CActor>(*)();
        
        template<typename T>
        std::unique_ptr<CActor> allocateActor()
        {
            return std::make_unique<T>();
        }

        TAILS_API std::unique_ptr<CActor> allocateActor(const CString& name);
        TAILS_API bool registerActorImpl(const CString& name, AllocateActorFunc allocFunc);

        template<typename T>
        struct TActorRegistryEntry final
        {
            TActorRegistryEntry() = delete;
            explicit TActorRegistryEntry(const CString& name)
            {
                registerActorImpl(name, allocateActor<T>);
            }
            TActorRegistryEntry(const TActorRegistryEntry&) = delete;
            TActorRegistryEntry(TActorRegistryEntry&&) = delete;
            TActorRegistryEntry& operator=(const TActorRegistryEntry&) = delete;
            TActorRegistryEntry& operator=(TActorRegistryEntry&&) = delete;
            ~TActorRegistryEntry() = default;
        };
    }
}

/**
 * Registers an actor with the actor registry, so it can be allocated via just its string name
 * @param CLASS Actor class
 * @param NAME Friendly name
 */
#define TAILS_REGISTER_ACTOR(CLASS, NAME) \
    template<typename> struct TActorRegistration; \
    template<> struct TActorRegistration<CLASS> \
    { \
        static const ::tails::impl::TActorRegistryEntry<CLASS> gActorRegistrar; \
    }; \
    const ::tails::impl::TActorRegistryEntry<CLASS> TActorRegistration<CLASS>::gActorRegistrar {NAME};

#endif // TAILS_ACTOR_REGISTRY_HPP
