#include <Tails/Debug.hpp>

#ifdef TAILS_DEBUG
#include <Tails/Log.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/String.hpp>

#include <SDL3/SDL_render.h>

#include <vector>
#endif // TAILS_DEBUG

namespace tails::debug
{
    namespace
    {
#ifdef TAILS_DEBUG
        struct SDebugMessage
        {
            CString message;
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

    void addOnScreenDebugMessage(const float duration, const CString& msg)
    {
#ifdef TAILS_DEBUG
        gDebugMessages.push_back({
            .message = msg,
            .duration = duration,
            .timer = 0.f
        });
#endif // TAILS_DEBUG
    }
}
