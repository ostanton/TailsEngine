#include <Tails/Log.hpp>

// TODO - look into SDL logging
#include <SDL3/SDL_log.h>

#include <memory>
#include <iostream>

namespace tails::logger
{
    void init()
    {
        
    }

    void log(
        const ELogCategory category,
        const ELogSeverity severity,
        const char* message,
        const SLogDetails& details
    )
    {
#ifdef TAILS_ENABLE_LOGGING
        std::cout << message << '\n';
#endif // TAILS_ENABLE_LOGGING
    }
}
