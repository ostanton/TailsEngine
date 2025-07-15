#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/Audio/BusHandle.hpp>
#include <Tails/Assets/Sound.hpp>
#include <Tails/Log.hpp>
#include <Tails/String.hpp>

#include <SDL3/SDL_audio.h>

#include <vector>

namespace tails::audio
{
    namespace
    {
        /**
         * A bus is a "thing" which can play sounds (one-shots, music, etc.).
         * It has a name, volume, etc. (typical stuff you might see in a DAW) in addition to concurrency settings.
         * Buses are generally used to group sounds together. You might have a bus for:
         * - UI SFX,
         * - Music,
         * - Dialogue,
         * - etc.
         *
         * Multiple sounds can be played concurrently on a single bus. How many can be played, etc. is controlled
         * via the bus' concurrency settings.
         *
         * TODO - possibly make this a SoA?
         */
        struct SBus final
        {
            CString name;
            float volume;
            /** Whether this bus is current playing anything */
            bool playing;
            SConcurrencySettings concurrencySettings;
            SDL_AudioStream* stream;
        };

        SDL_AudioDeviceID gDeviceId;
        std::vector<SBus> gBuses;

        SBus* getBus(const usize index)
        {
            if (index < gBuses.size())
                return &gBuses[index];

            return nullptr;
        }
    }

    void init()
    {
        gDeviceId = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
        if (gDeviceId == 0)
        {
            TAILS_LOG(AudioSubsystem, Error, TAILS_FMT("Failed to open audio device: '{}'", SDL_GetError()));
            return;
        }

        TAILS_LOG(AudioSubsystem, Message, TAILS_FMT("Using '{}' audio device", SDL_GetAudioDeviceName(gDeviceId)));

        TAILS_LOG(AudioSubsystem, Message, "Initialised");
    }

    void deinit()
    {
        gBuses.clear();

        TAILS_LOG(AudioSubsystem, Message, "Deinitialised");
    }

    SBusHandle addBus(
        CString name,
        const float volume,
        const SConcurrencySettings concurrencySettings
    )
    {
        // TODO - get proper spec
        constexpr SDL_AudioSpec spec {
            .format = SDL_AUDIO_F32,
            .channels = 1,
            .freq = 8000,
        };
        auto const stream = SDL_CreateAudioStream(&spec, nullptr);
        SDL_BindAudioStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, stream);
        gBuses.emplace_back(
            std::move(name),
            volume,
            false,
            concurrencySettings,
            stream
        );

        return {gBuses.size() - 1};
    }

    SBusHandle getHandleFromName(const CString& name)
    {
        for (usize i {0}; auto& bus : gBuses)
        {
            if (bus.name == name)
                return {i};

            i++;
        }

        return {nullOpt};
    }

    void removeBus(const SBusHandle handle)
    {
        if (!handle.index.isValid())
            return;

        if (const usize index {handle.index.get()}; handle.index.get() < gBuses.size())
            gBuses.erase(gBuses.begin() + static_cast<std::vector<SBus>::difference_type>(index));
    }

    void SBusHandle::pause()
    {
        if (!index.isValid())
            return;

        // TODO
    }

    void SBusHandle::stop()
    {
        if (!index.isValid())
            return;

         // TODO
    }

    void SBusHandle::setVolume(const float volume)
    {
        if (!index.isValid())
            return;

        if (auto const bus = getBus(index.get()))
            bus->volume = volume;
    }

    void SBusHandle::setName(CString name)
    {
        if (!index.isValid())
            return;

        if (auto const bus = getBus(index.get()))
            bus->name = std::move(name);
    }

    void SBusHandle::playSound(std::shared_ptr<CSound> sound)
    {
        if (!index.isValid())
            return;

        // TODO
    }

    bool SBusHandle::isPlaying() const noexcept
    {
        if (!index.isValid())
            return false;

        if (auto const bus = getBus(index.get()))
            return bus->playing;

        return false;
    }

    float SBusHandle::getVolume() const noexcept
    {
        if (!index.isValid())
            return 0.f;

        if (auto const bus = getBus(index.get()))
            return bus->volume;

        return 0.f;
    }

    CString SBusHandle::getName() const noexcept
    {
        if (!index.isValid())
            return {};

        if (auto const bus = getBus(index.get()))
            return bus->name;

        return {};
    }
}
