#include <Tails/Application.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/SilverUI/WidgetSubsystem.hpp>
#include <Tails/Game/Actor.hpp>
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

    CAssetManager& IApplication::getAssetManager() noexcept
    {
        return m_assetManager;
    }

    const CAssetManager& IApplication::getAssetManager() const noexcept
    {
        return m_assetManager;
    }

    void IApplication::exit()
    {
        m_window.close();
    }

    bool IApplication::init(int argc, char* argv[])
    {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

        // init Tails systems
        input::init();
        debug::init();
        logger::init();
        ui::init();
        
        return true;
    }

    bool IApplication::run()
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
        }

        return false;
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
        }
    }

    void IApplication::tick(const float deltaSeconds)
    {
        input::tick();
        debug::tick(m_currentDeltaSeconds);
        
        m_level.onTick(deltaSeconds);

        ui::tick(m_currentDeltaSeconds);
    }

    void IApplication::render()
    {
        m_window.clear();

        // do some batch rendering or something idk
        m_window.render(m_level);
        m_level.cleanupActors();

        ui::render(m_window);
        debug::render(); // TODO - how to stop it flickering??

        m_window.present();
    }

    bool IApplication::shouldExit() const
    {
        return !m_window.isOpen();
    }

    void IApplication::setInstance(IApplication& instance)
    {
        gApplication = &instance;
    }
}
