#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Log.hpp>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_timer.h>

#ifdef TAILS_OS_PSP
#include <pspkernel.h>
PSP_MODULE_INFO(gAppCreateData.name, 0, 1, 0);
#endif // TAILS_OS_PSP

// TODO - multiple threads. The main thread where ticking, rendering, etc. is done, then
// the asset loading thread, where assets and other things are loaded. This makes them
// non-blocking on the main thread. So loading a level becomes loading an asset on
// the asset loading thread, same with other stuff, etc.

namespace tails
{
    namespace
    {
        IApplication* gApplication {nullptr};
        float gDeltaSeconds {0.f};
    }

    int SEntryPoint::main(const int argc, char* argv[], IApplication& app)
    {
        gApplication = &app;

        // TODO - abstract into user-friendly arg struct
        if (!app.init(argc, argv))
            return 0;

        app.run();
        app.shutdown();

        return 0;
    }

    IApplication& getApplication() noexcept
    {
        return *gApplication;
    }

    float getDeltaSeconds() noexcept
    {
        return gDeltaSeconds;
    }

    float getFPS() noexcept
    {
        return 1.f / gDeltaSeconds;
    }

    CWindow& getWindow() noexcept
    {
        return gApplication->window;
    }

    IApplication::IApplication(const SVector2u windowSize)
        : window(gAppCreateData.name, windowSize)
    {
    }

    IApplication& IApplication::get()
    {
        return *gApplication;
    }

    void IApplication::exit()
    {
        window.close();
    }

    bool IApplication::init(int argc, char* argv[])
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

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

    void IApplication::run()
    {
        TAILS_LOG(Application, Message, "Starting main loop");
        auto timeNow = SDL_GetPerformanceCounter();
        
        while (!shouldExit())
        {
            const auto timeLast = timeNow;
            timeNow = SDL_GetPerformanceCounter();
            gDeltaSeconds =
                static_cast<float>((timeNow - timeLast) * 1000) /
                    static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
            
            pollInput();
            tick(gDeltaSeconds);
            render();
            cleanup();
        }

        TAILS_LOG(Application, Message, "Finished main loop");
    }

    void IApplication::shutdown()
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

    void IApplication::pollInput()
    {
        while (const auto ev = window.pollEvent())
        {
            onInputEvent(*ev);
            ui::processEvent(*ev);
        }
    }

    void IApplication::tick(const float deltaSeconds)
    {
        input::tick();
        debug::tick(deltaSeconds);
        world::tick(deltaSeconds);
    }

    void IApplication::render()
    {
        window.getRenderer().clear();

        world::render(window.getRenderer());
        // TODO - might want this on a separate thread in the future
        ui::paint(window.getRenderer(), gDeltaSeconds);
        debug::render(window.getRenderer());

        window.getRenderer().present();
    }

    void IApplication::cleanup()
    {
        world::cleanup();
    }

    bool IApplication::shouldExit() const
    {
        return !window.isOpen();
    }
}
