#include <Tails/Subsystems/RegistrySubsystem.hpp>
#include <Tails/Registries/Registry.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    RegistryBase* RegistrySubsystem::getRegistry(const std::string& name)
    {
        if (!m_registries.contains(name)) return nullptr;

        return m_registries[name].get();
    }

    void RegistrySubsystem::initRegistry(const std::string& name, RegistryBase* registry)
    {
        Debug::print("  Initialising " + name + " m_registry...");
        registry->init(*this);
        Debug::print("  " + name + " initialised.");
    }
}
