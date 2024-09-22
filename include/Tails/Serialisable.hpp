#ifndef TAILS_SERIALISABLE_HPP
#define TAILS_SERIALISABLE_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json_fwd.hpp>

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
        virtual void serialise(nlohmann::json& obj) const = 0;
        virtual void deserialise(const nlohmann::json& obj) = 0;
        
        /**
         * "Reflectable" class name. If this class is not registered in a
         * class registry subclass, set this in the constructor instead.
         */
        std::string m_className;
    };
}

#endif // TAILS_SERIALISABLE_HPP
