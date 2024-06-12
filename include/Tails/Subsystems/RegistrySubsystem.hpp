#ifndef TAILS_REGISTRYSUBSYSTEM_HPP
#define TAILS_REGISTRYSUBSYSTEM_HPP

#include <Tails/Subsystems/Subsystem.hpp>

#include <unordered_map>
#include <memory>
#include <string>

namespace tails
{
    class RegistryBase;

    class TAILS_API RegistrySubsystem : public Subsystem
    {
    public:
        template<typename T>
        T* getRegistry(const std::string& name)
        {
            static_assert(std::is_base_of_v<RegistryBase, T>, "Failed to get m_registry, type does not derive RegistryBase.");
            return static_cast<T*>(getRegistry(name));
        }

        RegistryBase* getRegistry(const std::string& name);

    protected:
        void init(Engine& engine) override {}

        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        template<typename T>
        void emplaceRegistry(const std::string& name)
        {
            static_assert(std::is_base_of_v<RegistryBase, T>, "Failed to emplace m_registry, it does not derive RegistryBase");
            m_registries.emplace(std::pair(name, std::make_unique<T>()));
            initRegistry(name, m_registries[name].get());
        }

    private:
        void initRegistry(const std::string& name, RegistryBase* registry);

        std::unordered_map<std::string, std::unique_ptr<RegistryBase>> m_registries;
    };
}

#endif // TAILS_REGISTRYSUBSYSTEM_HPP
