#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Core.hpp>

namespace tails::debug
{
    TAILS_API void init();
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render();
    TAILS_API void deinit();

    // TODO - C-formatted or modern format (probably C-formatted!)
    TAILS_API void addOnScreenDebugMessage(const char* message, float duration);
}

#define TAILS_DEBUG_PRINT(MSG, DURATION) \
    ::tails::debug::addOnScreenDebugMessage(MSG, DURATION)

#endif // TAILS_DEBUG_HPP
