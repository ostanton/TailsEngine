#ifndef TAILS_SERIALISABLE_HPP
#define TAILS_SERIALISABLE_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json.hpp>

#include <memory>
#include <string>

namespace tails
{
    class CClassRegistry;

    /**
     * Separate into POD serialisable and more Unreal-style serialisation?
     */
    class TAILS_API ISerialisable
    {
        friend CClassRegistry;
        
    public:
        ISerialisable() = default;
        ISerialisable(const ISerialisable&) = default;
        ISerialisable(ISerialisable&&) noexcept = default;
        virtual ~ISerialisable() = default;
        ISerialisable& operator=(const ISerialisable&) = default;
        ISerialisable& operator=(ISerialisable&&) noexcept = default;

        template<typename T>
        std::unique_ptr<T> clone()
        {
            static_assert(std::is_base_of_v<ISerialisable, T>,
                "Failed to clone, specified type does not derive ISerialisable.");

            // TODO - test! Dunno if this kinda thing is intended or not
            return {static_cast<T*>(clone().release())};
        }

        [[nodiscard]] const std::string& getClassName() const {return m_className;}
        
    protected:
        virtual [[nodiscard]] nlohmann::json serialise() const = 0;
        virtual void deserialise(const nlohmann::json& obj) = 0;
        virtual [[nodiscard]] std::unique_ptr<ISerialisable> clone() const = 0;

    private:
        std::string m_className;
    };
}

#endif // TAILS_SERIALISABLE_HPP
