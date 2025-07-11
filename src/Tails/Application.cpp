#include <Tails/Application.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Audio/AudioSubsystem.hpp>
#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Log.hpp>
#include <Tails/Input/Event.hpp>

#include "ApplicationImpl.hpp"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_hints.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>

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
        SDL_Window* gWindowPtr {nullptr};

        SDL_WindowFlags getSDLWindowFlags(const TBitset<EWindowFlags> flags)
        {
            if (!flags.anyBitSet())
                return 0;

            SDL_WindowFlags result {0};
            if (flags.isBitSet(EWindowFlags::Resizable))
                result |= SDL_WINDOW_RESIZABLE;

            if (flags.isBitSet(EWindowFlags::Fullscreen))
                result |= SDL_WINDOW_FULLSCREEN;

            if (flags.isBitSet(EWindowFlags::Borderless))
                result |= SDL_WINDOW_BORDERLESS;

            if (flags.isBitSet(EWindowFlags::Minimised))
                result |= SDL_WINDOW_MINIMIZED;

            if (flags.isBitSet(EWindowFlags::Maximised))
                result |= SDL_WINDOW_MAXIMIZED;

            return result;
        }
    }

    namespace impl
    {
        SDL_Window* getWindow()
        {
            return gWindowPtr;
        }
    }

    bool init(int argc, char* argv[], const SWindowInfo& windowInfo)
    {
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD))
            return false;

        SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

        // initialise global application variables
        gCurrentFrameInfo = {};
        gShouldExit = false;
        gStartTime = SDL_GetPerformanceCounter();
        gWindowPtr = SDL_CreateWindow(
            windowInfo.title,
            0,
            0,
            getSDLWindowFlags(windowInfo.flags)
        );
        if (!gWindowPtr)
            return false;

        // Setup window
        SDL_SetWindowMinimumSize(
            gWindowPtr,
            static_cast<int>(windowInfo.minSize.x),
            static_cast<int>(windowInfo.minSize.y)
        );

        // init Tails systems
        logger::init();
        render::init();
        assets::init();
        input::init();
        audio::init();
        debug::init();
        world::init();
        ui::init();

        // Force renderer to update to match window size
        SDL_SetWindowSize(
            gWindowPtr,
            static_cast<int>(windowInfo.size.x),
            static_cast<int>(windowInfo.size.y)
        );

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
        render::deinit();

        SDL_DestroyWindow(gWindowPtr);
        gWindowPtr = nullptr;
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
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            TOptional<CEvent> evt;
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
                evt.emplace(CEvent::SClosed {});
                break;
            case SDL_EVENT_WINDOW_RESIZED:
                evt.emplace(CEvent::SResized {
                    .size = {ev.window.data1, ev.window.data2}
                });
                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                evt.emplace(CEvent::SMouseButtonDown {
                    .button = static_cast<mouse::EButton>(ev.button.button),
                    .position = {ev.button.x, ev.button.y}
                });
                break;
            case SDL_EVENT_MOUSE_BUTTON_UP:
                evt.emplace(CEvent::SMouseButtonUp {
                    .button = static_cast<mouse::EButton>(ev.button.button),
                    .position = {ev.button.x, ev.button.y}
                });
                break;
            case SDL_EVENT_MOUSE_MOTION:
                evt.emplace(CEvent::SMouseMove {
                    .position = {ev.motion.x, ev.motion.y}
                });
                break;
            case SDL_EVENT_KEY_DOWN:
                evt.emplace(CEvent::SKeyDown {
                    .key = {
                        .code = ev.key.key,
                        .type = EKeyType::Keyboard
                    }
                });
                break;
            case SDL_EVENT_KEY_UP:
                evt.emplace(CEvent::SKeyUp {
                    .key = {
                        .code = ev.key.key,
                        .type = EKeyType::Keyboard
                    }
                });
                break;
            default:
                break;
            }

            if (!evt)
                continue;

            if (callback)
                callback(*evt);
            ui::processEvent(*evt);

            if (evt->is<CEvent::SClosed>())
                exit();
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
        render::clear();

        world::render();
        ui::paint(gCurrentFrameInfo.getDeltaSeconds());
        debug::render();

        render::present();
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
