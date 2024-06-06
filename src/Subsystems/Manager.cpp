#include <Tails/Subsystems/Manager.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Managers/Asset.hpp>
#include <Tails/Managers/Input.hpp>
#include <Tails/Managers/Audio.hpp>

namespace tails
{
    void ManagerSubsystem::addManager(const std::string& name, std::unique_ptr<Manager> manager)
    {
        Debug::print("      Initialising " + name + " manager...");
        m_managers[name] = std::move(manager);
        m_managers[name]->added(*this);
        Debug::print("      " + name + " manager initialised.");
    }

    void ManagerSubsystem::destroyManager(const std::string& name)
    {
        if (!m_managers.contains(name)) return;

        Debug::print("  Destroying " + name + " manager...");
        m_managers[name]->pendingDestroy = true;
    }

    void ManagerSubsystem::clearManagers()
    {
        if (m_managers.empty()) return;

        m_managers.clear();
    }

    Manager* ManagerSubsystem::getManager(const std::string& name)
    {
        if (!m_managers.contains(name)) return nullptr;

        return m_managers[name].get();
    }

    InputManager& ManagerSubsystem::getInputManager()
    {
        return *getManager<InputManager>("input");
    }

    AudioManager& ManagerSubsystem::getAudioManager()
    {
        return *getManager<AudioManager>("audio");
    }

    AssetManager& ManagerSubsystem::getAssetManager()
    {
        return *getManager<AssetManager>("asset");
    }

    void ManagerSubsystem::init()
    {
        Debug::print("    Initialise managers:");
        createManager<AssetManager>("asset");
        createManager<InputManager>("input");
        createManager<AudioManager>("audio");
        Debug::print("    Managers initialised!");
    }

    void ManagerSubsystem::preTick()
    {
        for (auto& managerPair : m_managers)
        {
            managerPair.second->preTick();

            if (managerPair.second->pendingCreate)
                managerPair.second->pendingCreate = false;
        }
    }

    void ManagerSubsystem::tick(float deltaTime)
    {
        for (auto& managerPair : m_managers)
        {
            if (!managerPair.second->pendingCreate)
                managerPair.second->tick(deltaTime);
        }
    }

    void ManagerSubsystem::postTick()
    {
        for (auto it {m_managers.begin()}; it != m_managers.end();)
        {
            (*it).second->postTick();

            if ((*it).second->pendingDestroy)
            {
                Debug::print("  " + (*it).first + " manager destroyed.");
                (*it).second->removed();
                m_managers.erase(it);
            }
            else
                ++it;
        }
    }

    void ManagerSubsystem::deinit()
    {
        Debug::print("    Removing managers:");
        for (auto& managerPair : m_managers)
        {
            Debug::print("      Removing " + managerPair.first + " manager...");
            managerPair.second->removed();
            Debug::print("      " + managerPair.first + " manager removed.");
        }

        Debug::print("    Managers removed.\n");

        Debug::print("    Destroying managers...");
        m_managers.clear();
        Debug::print("    Managers destroyed.");
    }
}
