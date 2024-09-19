#ifndef TAILS_PRIV_SERIALISABLE_HPP
#define TAILS_PRIV_SERIALISABLE_HPP

#include <Tails/Debug.hpp>

#include <map>
#include <string>

namespace tails
{
class ISerialisable;

namespace priv
{
    using CreateObjectFunc = ISerialisable*(*)();
    using SerialisableMap = std::map<std::string, CreateObjectFunc>;

    inline SerialisableMap& getSerialisableRegistry()
    {
        static SerialisableMap registryMap;
        return registryMap;
    }

    template<typename T>
    ISerialisable* createObject()
    {
        static_assert(std::is_base_of_v<ISerialisable, T>,
            "Cannot create object, it does not derive ISerialisable.");
        return new T;
    }

    template<typename T>
    struct SRegistryEntry
    {
        SRegistryEntry(const SRegistryEntry&) = delete;
        SRegistryEntry& operator=(const SRegistryEntry&) = delete;

        static SRegistryEntry& get(const std::string& name)
        {
            static SRegistryEntry instance(name);
            return instance;
        }

    private:
        SRegistryEntry(const std::string& name)
        {
            SerialisableMap& registry {getSerialisableRegistry()};
            CreateObjectFunc func {createObject<T>};

            const std::pair result {registry.insert(SerialisableMap::value_type(name, func))};

            if (!result.second)
            {
                CDebug::error("Object ID ", name, " is already registered.");
                return;
            }

            CDebug::print("Registered ID ", name, " of type ", typeid(T).name(), " of size ", sizeof(T));
        }
    };
} // priv
} // tails

#endif // TAILS_PRIV_SERIALISABLE_HPP
