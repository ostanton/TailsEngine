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
        virtual ~ISerialisable() = default;

        template<typename T>
        std::unique_ptr<T> clone()
        {
            static_assert(std::is_base_of_v<ISerialisable, T>,
                "Failed to clone, specified type does not derive ISerialisable.");
            
            return std::static_pointer_cast<T>(clone());
        }

        const std::string& getClassName() const {return m_className;}
        
    protected:
        virtual nlohmann::json serialise() = 0;
        virtual void deserialise(const nlohmann::json& obj) = 0;
        virtual std::unique_ptr<ISerialisable> clone() = 0;

    private:
        std::string m_className;
    };
}

#endif // TAILS_SERIALISABLE_HPP
