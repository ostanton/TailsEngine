#ifndef TAILS_SERIALISABLE_HPP
#define TAILS_SERIALISABLE_HPP

#include <Tails/Config.hpp>
#include <Tails/priv/Serialisable.hpp>

#include <nlohmann/json.hpp>

#include <string>

namespace tails
{
    class TAILS_API ISerialisable
    {
    public:
        ISerialisable() = default;
        ISerialisable(const ISerialisable&) = default;
        ISerialisable(ISerialisable&&) noexcept = default;
        virtual ~ISerialisable() = default;
        ISerialisable& operator=(const ISerialisable&) = default;
        ISerialisable& operator=(ISerialisable&&) noexcept = default;

        [[nodiscard]] const std::string& getClassName() const {return m_className;}
        
    protected:
        [[nodiscard]] virtual nlohmann::json serialise() const = 0;
        virtual void deserialise(const nlohmann::json& obj) = 0;
        
        /**
         * "Reflectable" class name. If this class is not registered in a
         * class registry subclass, set this in the constructor instead.
         */
        std::string m_className;
    };
}

#define TAILS_REGISTER_CLASS_CUSTOM_NAME(TYPE, NAME) \
    namespace tails { \
    namespace priv { \
    namespace { \
        template<typename T> \
        class CSerialisableRegistration; \
        template<> \
        class CSerialisableRegistration<TYPE> { \
            static const ::tails::priv::SRegistryEntry<TYPE>& m_reg; \
        }; \
        const ::tails::priv::SRegistryEntry<TYPE>& CSerialisableRegistration<TYPE>::m_reg = ::tails::priv::SRegistryEntry<TYPE>::get(NAME); \
    }}}

#define TAILS_REGISTER_CLASS(TYPE) TAILS_REGISTER_CLASS_CUSTOM_NAME(TYPE, #TYPE)

#endif // TAILS_SERIALISABLE_HPP
