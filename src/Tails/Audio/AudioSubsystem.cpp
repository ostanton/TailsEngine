#include <Tails/Audio/AudioSubsystem.hpp>

#include <SDL3/SDL_audio.h>

#include <unordered_map>

namespace tails::audio
{
    struct SBus final
    {
        float volume;
        bool playing;
        TAssetPtr<CSound> currentSound;
    };

    namespace
    {
        usize gNextBusIndex {0};
        std::unordered_map<usize, SBus> gBuses;

        SBus* getBus(const SBusHandle handle)
        {
            if (gBuses.find(handle) != gBuses.end())
                return &gBuses[handle];

            return nullptr;
        }
    }
    
    void init()
    {
        
    }

    SBusHandle addBus()
    {
        gBuses.try_emplace(gNextBusIndex++);
        return gBuses.size() - 1;
    }

    void removeBus(const SBusHandle handle)
    {
        if (handle >= gBuses.size())
            return;

        gBuses.erase(handle);
    }

    void setBusVolume(const SBusHandle handle, const float volume)
    {
        if (auto const bus = getBus(handle))
            bus->volume = volume;
    }

    float getBusVolume(const SBusHandle handle)
    {
        if (auto const bus = getBus(handle))
            return bus->volume;

        return 0.f;
    }

    bool isBusPlaying(const SBusHandle handle)
    {
        if (auto const bus = getBus(handle))
            return bus->playing;
        
        return false;
    }

    void playSoundInBus(const SBusHandle handle, const TAssetPtr<CSound>& sound)
    {
        auto const bus = getBus(handle);
        if (!bus)
            return;
        
        bus->currentSound = sound;
        bus->playing = true;
        // TODO - actually play the sound via SDL or something!
    }

    void stopBus(const SBusHandle handle)
    {
        if (auto const bus = getBus(handle))
            bus->playing = false;
    }
}
