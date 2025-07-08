#ifndef TAILS_AUDIO_SUBSYSTEM_HPP
#define TAILS_AUDIO_SUBSYSTEM_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class CString;
}

namespace tails::audio
{
    struct SBusHandle;

    struct TAILS_API SConcurrencySettings final
    {
        usize maxSounds {10};
    };
    
    TAILS_API void init();
    TAILS_API void deinit();
    TAILS_API SBusHandle addBus(
        CString name,
        float volume = 1.f,
        SConcurrencySettings concurrencySettings = {}
    );
    TAILS_API SBusHandle getHandleFromName(const CString& name);
    TAILS_API void removeBus(SBusHandle handle);
    TAILS_API void removeBus(const CString& name);
}

#endif // TAILS_AUDIO_SUBSYSTEM_HPP
