#ifndef TAILS_CLASS_REGISTRY_HPP
#define TAILS_CLASS_REGISTRY_HPP

#include <Tails/Debug.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Assert.hpp>

#include <map>
#include <string>

namespace tails
{
    namespace impl
    {
        using CreateObjectFunc = void*(*)();
        using ClassRegistryMap = std::map<std::string, CreateObjectFunc>;

        inline ClassRegistryMap& getClassRegistry()
        {
            static ClassRegistryMap registryMap;
            return registryMap;
        }

        template<typename T>
        void* createObjectImpl()
        {
            return new T;
        }

        template<typename T>
        struct SRegistryEntry final
        {
            SRegistryEntry(const SRegistryEntry&) = delete;
            SRegistryEntry(SRegistryEntry&&) = delete;
            SRegistryEntry& operator=(const SRegistryEntry&) = delete;
            SRegistryEntry& operator=(SRegistryEntry&&) = delete;
            ~SRegistryEntry() = default;

            static SRegistryEntry& get(const std::string& name)
            {
                static SRegistryEntry instance(name);
                return instance;
            }

        private:
            SRegistryEntry(const std::string& name)
            {
                debug::flush();
                debug::print("ClassRegistry - Trying to register ", name);
                ClassRegistryMap& registry {getClassRegistry()};
                CreateObjectFunc func {createObjectImpl<T>};

                const std::pair result {registry.insert(ClassRegistryMap::value_type(name, func))};

                if (!result.second)
                {
                    debug::error("ClassRegistry - Object ID ", name, " is already registered.");
                    return;
                }

                debug::print("ClassRegistry - Registered ID ", name, " of type ", typeid(T).name(), " of size ", sizeof(T));
            }
        };
    } // priv

    /**
     * Constructs an object registered in the class registry of the specified class name and returns as void*
     * @param name Registered class name
     * @return Constructed class data
     */
    inline void* constructClass(const std::string_view name)
    {
        auto& reg = impl::getClassRegistry();
        const auto it = reg.find(name.data());

        if (it == reg.end())
        {
            debug::error("ClassRegistry - Failed to create object with ID \"", name, "\". It is not registered.");
            return nullptr;
        }

        return it->second();
    }

    /**
     * Constructs an object registered in the class registry and casts it to the specified type
     * @tparam T Class type
     * @param name Registered class name
     * @return Constructed class object
     */
    template<UserType T>
    T* constructClass(const std::string_view name)
    {
        return static_cast<T*>(constructClass(name));
    }
} // tails

#define TAILS_REGISTER_CLASS_CUSTOM_NAME(TYPE, NAME) \
    namespace tails { \
    namespace impl { \
    namespace { \
        template<::tails::UserType T> \
        class CClassRegistration; \
        template<> \
        class CClassRegistration<TYPE> { \
            static const ::tails::impl::SRegistryEntry<TYPE>& m_reg; \
        }; \
        const ::tails::impl::SRegistryEntry<TYPE>& CClassRegistration<TYPE>::m_reg = \
            ::tails::impl::SRegistryEntry<TYPE>::get(NAME); \
    }}}

#define TAILS_REGISTER_CLASS(TYPE) TAILS_REGISTER_CLASS_CUSTOM_NAME(TYPE, #TYPE)

#define TAILS_CLASS(CLASS) \
    static std::string getClassName() {return #CLASS;}

#endif // TAILS_CLASS_REGISTRY_HPP
