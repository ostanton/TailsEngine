#include <Tails/Debug.hpp>

#ifdef TAILS_DEBUG
#include <Tails/Log.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/String.hpp>

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_render.h>

#include <vector>
#include <cstdarg>
#endif // TAILS_DEBUG

namespace tails::debug
{
    namespace
    {
#ifdef TAILS_DEBUG
        struct SDebugMessage
        {
            const char* message;
            float duration;
            float timer;
        };
        
        std::vector<SDebugMessage> gDebugMessages;
#endif // TAILS_DEBUG
    }

    void init()
    {
#ifdef TAILS_DEBUG
        TAILS_LOG(DebugSubsystem, Message, "Initialised");
#endif // TAILS_DEBUG
    }

    void tick(const float deltaSeconds)
    {
#ifdef TAILS_DEBUG
        for (auto it {gDebugMessages.rbegin()}; it != gDebugMessages.rend();)
        {
            if (it->timer >= it->duration)
                it = decltype(it)(gDebugMessages.erase(std::next(it).base()));
            else
            {
                it->timer += deltaSeconds;
                ++it;
            }
        }
#endif // TAILS_DEBUG
    }

    void render()
    {
#ifdef TAILS_DEBUG
        for (const auto& message : gDebugMessages)
        {
            render::debugText(
                {
                    0.f,
                    1.f,
                    static_cast<float>(gDebugMessages.size()) * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE
                },
                message.message
            );
        }
#endif // TAILS_DEBUG
    }

    void deinit()
    {
#ifdef TAILS_DEBUG
        gDebugMessages.clear();

        TAILS_LOG(DebugSubsystem, Message, "Deinitialised");
#endif // TAILS_DEBUG
    }

    void addOnScreenDebugMessage(const float duration, const char* fmt, ...)
    {
#ifdef TAILS_DEBUG
        std::va_list args;
        va_start(args, fmt);
        const int len {SDL_vsnprintf(nullptr, 0, fmt, args)};
        va_end(args);

        auto const msg {static_cast<char*>(SDL_malloc(len + 1))};
        va_start(args, fmt);
        if (SDL_vsnprintf(msg, len + 1, fmt, args) < 0)
        {
            TAILS_LOG(DebugSubsystem, Error, "Failed to format on-screen debug message");
            va_end(args);
            return;
        }
        va_end(args);
        
        gDebugMessages.push_back({msg, duration, 0.f});
#endif // TAILS_DEBUG
    }
}
