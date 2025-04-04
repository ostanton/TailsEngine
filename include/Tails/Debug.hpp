#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Core.hpp>

namespace tails::debug
{
    void init();
    void tick(float deltaSeconds);
    void render();

    // TODO - C-formatted or modern format (probably C-formatted!)
    void addOnScreenDebugMessage(const char* message, float duration);
}

#define TAILS_DEBUG_PRINT(MSG, DURATION) \
    ::tails::debug::addOnScreenDebugMessage(MSG, DURATION)

#endif // TAILS_DEBUG_HPP
