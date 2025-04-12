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
        const ECategory category,
        const ESeverity severity,
        const char* message,
        const SDetails& details
    )
    {
#ifdef TAILS_ENABLE_LOGGING
        std::cout << message << '\n';
#endif // TAILS_ENABLE_LOGGING
    }
}

