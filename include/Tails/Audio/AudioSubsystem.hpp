#ifndef TAILS_AUDIO_SUBSYSTEM_HPP
#define TAILS_AUDIO_SUBSYSTEM_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class CSound;
}

namespace tails::audio
{
    struct SBus;
    using SBusHandle = usize;
    
    TAILS_API void init();
    TAILS_API void deinit();
    TAILS_API SBusHandle addBus();
    TAILS_API void removeBus(SBusHandle handle);
    TAILS_API void setBusVolume(SBusHandle handle, float volume);
    TAILS_API float getBusVolume(SBusHandle handle);
    TAILS_API bool isBusPlaying(SBusHandle handle);
    TAILS_API void playSoundInBus(SBusHandle handle, std::shared_ptr<CSound> sound);
    TAILS_API void stopBus(SBusHandle handle);
}

#endif // TAILS_AUDIO_SUBSYSTEM_HPP
