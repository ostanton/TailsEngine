#include <Tails/Subsystems/AudioSubsystem.hpp>
#include <Tails/Audio/Bus.hpp>

namespace tails
{
    AudioSubsystem::AudioSubsystem() = default;
    AudioSubsystem::~AudioSubsystem() = default;

    size_t AudioSubsystem::addBus(std::unique_ptr<Bus> bus)
    {
        m_buses.emplace_back(std::move(bus));
        return m_buses.size() - 1;
    }

    Bus* AudioSubsystem::getBus(size_t index)
    {
        if (index >= m_buses.size()) return nullptr;

        return m_buses[index].get();
    }

    void AudioSubsystem::tick(float deltaTime)
    {
        // something here??
    }
}
