#include <Tails/Subsystems/SubsystemManager.hpp>
#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    C* SubsystemManager::getSubsystem(const std::string& name)
    {
        if (!m_subsystems.contains(name)) return nullptr;

        return m_subsystems[name].get();
    }

    void SubsystemManager::addSubsystem(const std::string& name, std::unique_ptr<C> subsystem)
    {
        Debug::print("  Initialising " + name + " subsystem...");
        m_subsystems[name] = std::move(subsystem);
        m_subsystems[name]->outer = this;
        m_subsystems[name]->init();
        Debug::print("  " + name + " subsystem initialised.");
    }

    bool SubsystemManager::destroySubsystem(const std::string& name)
    {
        if (!m_subsystems.contains(name)) return false;

        m_subsystems[name]->pendingDestroy = true;
        return true;
    }

    void SubsystemManager::preTick()
    {
        for (auto& subsystemPair : m_subsystems)
        {
            subsystemPair.second->preTick();

            if (subsystemPair.second->pendingCreate)
                subsystemPair.second->pendingCreate = true;
        }
    }

    void SubsystemManager::tick(float deltaTime)
    {
        for (auto& subsystemPair : m_subsystems)
        {
            if (!subsystemPair.second->pendingCreate)
                subsystemPair.second->tick(deltaTime);
        }
    }

    void SubsystemManager::draw(sf::RenderTarget& target)
    {
        for (auto& subsystemPair : m_subsystems)
        {
            if (!subsystemPair.second->pendingCreate)
                target.draw(*subsystemPair.second);
        }
    }

    void SubsystemManager::postTick()
    {
        for (auto it {m_subsystems.begin()}; it != m_subsystems.end();)
        {
            (*it).second->postTick();

            if ((*it).second->pendingDestroy)
            {
                Debug::print("  " + (*it).first + " subsystem destroyed.");
                (*it).second->deinit();
                m_subsystems.erase(it);
            }
            else
                ++it;
        }
    }
}
