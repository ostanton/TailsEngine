#include <Tails/Debug.hpp>
#include <Tails/Log.hpp>

#include <vector>

#ifdef TAILS_OS_PSP
#include <pspdebug.h>
#endif // TAILS_OS_PSP

// TODO - on screen messages should use platform agnostic SilverUI things.
// Log should use platform-specific prints like the console or PSP's debug screen

namespace tails::debug
{
    struct SDebugMessage
    {
        const char* message;
        float duration;
        float timer;
    };

    namespace
    {
        std::vector<SDebugMessage> gDebugMessages;
    }

    void init()
    {
#ifdef TAILS_OS_PSP
        pspDebugScreenInit();
#endif // TAILS_OS_PSP

        TAILS_LOG(DebugSubsystem, Message, "Initialised");
    }

    void tick(const float deltaSeconds)
    {
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
    }

    void render()
    {
#ifdef TAILS_OS_PSP
        pspDebugScreenSetXY(0, 0);
        for (const auto& message : gDebugMessages)
        {
            pspDebugScreenPrintf(message.message);
        }
#endif // TAILS_OS_PSP
    }

    void deinit()
    {
        gDebugMessages.clear();

        TAILS_LOG(DebugSubsystem, Message, "Deinitialised");
    }

    void addOnScreenDebugMessage(const char* message, const float duration)
    {
        gDebugMessages.push_back({message, duration, 0.f});
    }
}
