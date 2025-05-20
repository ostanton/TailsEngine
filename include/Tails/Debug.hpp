#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Core.hpp>

namespace tails::debug
{
    TAILS_API void init();
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render();
    TAILS_API void deinit();

    TAILS_API void addOnScreenDebugMessage(float duration, const char* fmt, ...);
}

#ifdef TAILS_DEBUG

#define TAILS_DEBUG_PRINT(DURATION, MSG) \
    ::tails::debug::addOnScreenDebugMessage(DURATION, MSG)

#define TAILS_DEBUG_PRINTF(DURATION, MSG, ...) \
    ::tails::debug::addOnScreenDebugMessage(DURATION, MSG, __VA_ARGS__)

#else

#define TAILS_DEBUG_PRINT(DURATION, MSG)
#define TAILS_DEBUG_PRINTF(DURATION, MSG, ...)

#endif // TAILS_DEBUG

#endif // TAILS_DEBUG_HPP
