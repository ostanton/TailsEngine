#ifndef TAILS_REGISTRY_HPP
#define TAILS_REGISTRY_HPP

#include <Tails/Config.hpp>
#include <Tails/Serialisable.hpp>

#include <string>
#include <unordered_map>
#include <memory>

namespace tails
{
    /**
     * A wrapper for mapping "prototype" object instances to literal class name strings, allowing for some
     * limited, yet useful, reflection.
     */
    class TAILS_API CClassRegistry
    {
    public:
        CClassRegistry() = default;
        CClassRegistry(const CClassRegistry& other);
        CClassRegistry(CClassRegistry&&) noexcept = default;
        virtual ~CClassRegistry();

        CClassRegistry& operator=(const CClassRegistry& other);
        CClassRegistry& operator=(CClassRegistry&&) = default;
        
        template<typename C>
        void registerClass(const std::string& name)
        {
            static_assert(std::is_base_of_v<ISerialisable, C>,
                "Failed to register class, it does not derive ISerialisable.");

            registerClass(name, std::make_unique<C>());
        }

        void registerClass(const std::string& name, std::unique_ptr<ISerialisable> classObj);

        [[nodiscard]] std::unique_ptr<ISerialisable> instantiateClass(const std::string& name);
        [[nodiscard]] bool classExists(const std::string& name) const;

        template<typename T>
        std::unique_ptr<T> instantiateClass(const std::string& name)
        {
            if (m_classes.contains(name))
            {
                std::unique_ptr<T> obj {static_cast<T*>(m_classes[name]->clone().release())};
                if (obj->m_className != name)
                    obj->m_className = name;
                return obj;
            }

            return nullptr;
        }
        
    private:
        /**
         * Instances of all the registered classes, mapped to their string names.
         * Could use void* or something here instead of an abstract base class... maybe.
         */
        std::unordered_map<std::string, std::unique_ptr<ISerialisable>> m_classes;
    };
}

#endif // TAILS_REGISTRY_HPP
