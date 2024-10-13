#include <Tails/AudioManager.hpp>
#include <Tails/Bus.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    IBus* CAudioManager::addBus(const std::string& busName, std::unique_ptr<IBus> bus)
    {
        if (get().m_buses.contains(busName)) return getBus(busName);
        
        auto result = get().m_buses.try_emplace(busName, std::move(bus));
        if (!result.second)
        {
            CDebug::error("Failed to add ", busName, " bus.");
            return nullptr;
        }
        
        return get().m_buses.at(busName).get();
    }

    IBus* CAudioManager::getBus(std::string_view busName)
    {
        if (!get().m_buses.contains(busName.data()))
        {
            CDebug::error(busName, " bus does not exist");
            return nullptr;
        }

        return get().m_buses.at(busName.data()).get();
    }

    bool CAudioManager::busExists(std::string_view busName)
    {
        return get().m_buses.contains(busName.data());
    }

    CAudioManager& CAudioManager::get()
    {
        static CAudioManager instance;
        return instance;
    }
}
