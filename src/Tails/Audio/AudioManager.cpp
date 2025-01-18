#include <Tails/Audio/AudioManager.hpp>
#include <Tails/Audio/Bus.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Maths.hpp>

namespace tails
{
    IBus* CAudioManager::addBus(std::string_view busName, std::unique_ptr<IBus> bus)
    {
        if (get().m_buses.contains(hash(busName))) return getBus(busName);
        
        auto result = get().m_buses.try_emplace(hash(busName), std::move(bus));
        if (!result.second)
        {
            debug::error("Failed to add ", busName, " bus.");
            return nullptr;
        }
        
        return get().m_buses.at(hash(busName)).get();
    }

    IBus* CAudioManager::getBus(std::string_view busName)
    {
        if (!get().m_buses.contains(hash(busName)))
        {
            debug::error(busName, " bus does not exist");
            return nullptr;
        }

        return get().m_buses.at(hash(busName)).get();
    }

    bool CAudioManager::busExists(std::string_view busName)
    {
        return get().m_buses.contains(hash(busName));
    }

    CAudioManager& CAudioManager::get()
    {
        static CAudioManager instance;
        return instance;
    }
}
