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
        CClassRegistry(const CClassRegistry& other) = default;
        CClassRegistry(CClassRegistry&&) noexcept = default;
        virtual ~CClassRegistry();

        CClassRegistry& operator=(const CClassRegistry& other) = default;
        CClassRegistry& operator=(CClassRegistry&&) = default;
        
        /**
         * Registers a "prototype" of the specified class and maps it to the input class name
         */
        template<typename C>
        void registerClass(const std::string& className)
        {
            static_assert(std::is_base_of_v<ISerialisable, C>,
                "Failed to register class, it does not derive ISerialisable.");

            registerClass(className, std::make_unique<C>());
        }

        void registerClass(const std::string& className, std::unique_ptr<ISerialisable> classObj);

        [[nodiscard]] std::unique_ptr<ISerialisable> instantiateClass(const std::string& name);
        [[nodiscard]] bool classExists(const std::string& name) const;

        template<typename T>
        std::unique_ptr<T> instantiateClass(const std::string& className)
        {
            if (m_classes.contains(className))
            {
                std::unique_ptr<T> obj {static_cast<T*>(m_classes[className]->clone().release())};
                if (obj->m_className != className)
                    obj->m_className = className;
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
