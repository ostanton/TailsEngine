#ifndef TAILS_REGISTRY_HPP
#define TAILS_REGISTRY_HPP

#include <Tails/JSON/JSONReader.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace tails
{
    class RegistrySubsystem;

    // abstract base class for registries
    class TAILS_API RegistryBase
    {
        friend RegistrySubsystem;

    public:
        virtual ~RegistryBase() = default;

    protected:
        virtual void init(RegistrySubsystem& subsystem) = 0;
    };

    template<typename Base>
    class TAILS_API Registry : public RegistryBase
    {
        static_assert(std::is_base_of_v<JSONReader, Base>, "Registry type must derive JSONReader.");

    public:
        // creates and adds an "empty" prototype/registrar into the m_registry, for use later
        // registrar meaning the class that derives Base and will be mapped to name
        template<typename T>
        void assignRegistrar(const std::string& name)
        {
            static_assert(std::is_base_of_v<Base, T>, "Failed to assign registrar, it does not derive Base type.");
            m_registrars.emplace(std::make_pair(name, std::make_unique<T>()));
        }

        // clones the registrar mapped to name and called its "load" method, then returns it
        std::unique_ptr<Base> loadRegistrar(const std::string& name, nlohmann::json& json)
        {
            if (!m_registrars.contains(name)) return nullptr;

            std::unique_ptr<Base> result = std::make_unique<Base>(m_registrars[name]->load(json));
            return std::move(result);
        }

    private:
        std::unordered_map<std::string, std::unique_ptr<Base>> m_registrars;
    };
}

#endif // TAILS_REGISTRY_HPP
