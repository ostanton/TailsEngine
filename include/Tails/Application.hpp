#ifndef TAILS_APPLICATION_HPP
#define TAILS_APPLICATION_HPP

#include <Tails/Core.hpp>

namespace tails
{
    class CEvent;

    struct TAILS_API SFrameInfo
    {
        u64 currentTime;
        u64 previousTime;
        [[nodiscard]] float getDeltaSeconds() const;
    };

    namespace app
    {
        using PollInputCallback = void(*)(const CEvent&);
        TAILS_API bool init(int argc, char* argv[]);
        TAILS_API void deinit();
        TAILS_API bool shouldExit();
        TAILS_API void run();
        TAILS_API void startFrame();
        TAILS_API void pollInput(PollInputCallback callback = nullptr); // TODO - do we want this?
        TAILS_API void tick(float deltaSeconds);
        TAILS_API void render();
        TAILS_API void endFrame();
        TAILS_API void exit();

        TAILS_API const SFrameInfo& getCurrentFrameInfo() noexcept;
    }
}

#endif // TAILS_APPLICATION_HPP
