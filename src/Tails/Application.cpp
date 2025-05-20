#include <Tails/Application.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Log.hpp>
#include <Tails/Window.hpp>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_timer.h>

#ifdef TAILS_OS_PSP
#include <pspkernel.h>
PSP_MODULE_INFO("Tails Engine", 0, 1, 0); // TODO - probably have to set with a #define TAILS_GAME_NAME or something
#endif // TAILS_OS_PSP

// TODO - multiple threads. The main thread where ticking, rendering, etc. is done, then
// the asset loading thread, where assets and other things are loaded. This makes them
// non-blocking on the main thread. So loading a level becomes loading an asset on
// the asset loading thread, same with other stuff, etc.

namespace tails
{
    float SFrameInfo::getDeltaSeconds() const
    {
        return static_cast<float>((currentTime - previousTime) * 1000) /
            static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
    }
}

namespace tails::app
{
    namespace
    {
        SFrameInfo gCurrentFrameInfo;
        bool gShouldExit;
        u64 gStartTime;
        // TODO - make it stop being a class (same with renderer!)
        // only one window and one renderer will ever exist!
        CWindow gWindow {"Tails Engine", {1280, 720}};
    }

    bool init(int argc, char* argv[])
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD))
            return false;

        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

        // initialise global application variables
        gCurrentFrameInfo = {};
        gShouldExit = false;
        gStartTime = SDL_GetPerformanceCounter();

        // init Tails systems
        logger::init();
        assets::init();
        input::init();
        audio::init();
        debug::init();
        world::init();
        ui::init();

        return true;
    }

    void deinit()
    {
        TAILS_LOG(Application, Message, "Shutting down application");
        ui::deinit();
        world::deinit();
        debug::deinit();
        audio::deinit();
        input::deinit();
        assets::deinit();
    
        SDL_Quit();
        TAILS_LOG(Application, Message, "Application shutdown successfully");
    }

    bool shouldExit()
    {
        return gShouldExit;
    }

    void run()
    {
        while (!gShouldExit)
        {
            startFrame();
            pollInput();
            tick(gCurrentFrameInfo.getDeltaSeconds());
            render();
            endFrame();
        }
    }

    void startFrame()
    {
        gCurrentFrameInfo.previousTime = gCurrentFrameInfo.currentTime;
        gCurrentFrameInfo.currentTime = SDL_GetPerformanceCounter();
    }

    void pollInput(const PollInputCallback callback)
    {
        while (const auto ev = gWindow.pollEvent())
        {
            if (callback)
                callback(*ev);
            ui::processEvent(*ev);
        }
    }

    void tick(const float deltaSeconds)
    {
        input::tick();
        debug::tick(deltaSeconds);
        world::tick(deltaSeconds);
    }

    void render()
    {
        gWindow.getRenderer().clear();

        world::render(gWindow.getRenderer());
        ui::paint(gWindow.getRenderer(), gCurrentFrameInfo.getDeltaSeconds());
        debug::render(gWindow.getRenderer());

        gWindow.getRenderer().present();
    }

    void endFrame()
    {
        world::cleanup();
    }

    void exit()
    {
        gShouldExit = true;
    }

    const SFrameInfo& getCurrentFrameInfo() noexcept
    {
        return gCurrentFrameInfo;
    }
}
