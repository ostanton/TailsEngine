#include <Tails/Application.hpp>
#include <Tails/EntryPoint.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/SilverUI/WidgetSubsystem.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
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

    IApplication::IApplication(const SVector2u windowSize)
        : m_window(gAppCreateData.name, windowSize)
    {
    }

    IApplication& IApplication::get()
    {
        return *gApplication;
    }

    float IApplication::getDeltaSeconds() const noexcept
    {
        return m_currentDeltaSeconds;
    }

    float IApplication::getFPS() const noexcept
    {
        return 1.f / m_currentDeltaSeconds;
    }

    float IApplication::getAverageFPS() const noexcept
    {
        // TODO - calculate average FPS!
        return m_averageFPS;
    }

    void IApplication::exit()
    {
        m_window.close();
    }

    bool IApplication::init(int argc, char* argv[])
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

        // init Tails systems
        assets::init();
        input::init();
        audio::init();
        debug::init();
        logger::init();
        world::init();
        ui::init();
        
        return true;
    }

    void IApplication::run()
    {
        auto timeNow = SDL_GetPerformanceCounter();
        
        while (!shouldExit())
        {
            const auto timeLast = timeNow;
            timeNow = SDL_GetPerformanceCounter();
            m_currentDeltaSeconds =
                static_cast<float>((timeNow - timeLast) * 1000) / static_cast<float>(SDL_GetPerformanceFrequency()) * 0.001f;
            
            pollInput();
            tick(m_currentDeltaSeconds);
            render();
            cleanup();
        }
    }

    void IApplication::shutdown()
    {
        SDL_Quit();
    }

    void IApplication::pollInput()
    {
        while (const auto ev = m_window.pollEvent())
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
        ui::tick(deltaSeconds);
    }

    void IApplication::render()
    {
        m_window.clear();

        world::render(m_window);
        ui::render(m_window);
        debug::render(); // TODO - how to stop it flickering??

        m_window.present();
    }

    void IApplication::cleanup()
    {
        world::cleanup();
    }

    bool IApplication::shouldExit() const
    {
        return !m_window.isOpen();
    }
}
