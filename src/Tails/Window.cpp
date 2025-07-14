#include <Tails/Window.hpp>
#include <Tails/Log.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>

#include "Tails/Input/Event.hpp"

namespace tails::window
{
    namespace
    {
        SDL_Window* gWindowPtr;

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

    bool init(const SWindowInfo& windowInfo)
    {
        gWindowPtr = SDL_CreateWindow(
            windowInfo.title,
            0,
            0,
            getSDLWindowFlags(windowInfo.flags)
        );
        if (!gWindowPtr)
        {
            TAILS_LOG(Window, Error, "Failed to initialise window");
            return false;
        }

        SDL_SetWindowMinimumSize(
            gWindowPtr,
            static_cast<int>(windowInfo.minSize.x),
            static_cast<int>(windowInfo.minSize.y)
        );
        return true;
    }

    void deinit()
    {
        SDL_DestroyWindow(gWindowPtr);
        gWindowPtr = nullptr;
    }

    TOptional<CEvent> pollInput()
    {
        SDL_Event ev;
        if (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
                return {CEvent::SClosed {}};
            case SDL_EVENT_WINDOW_RESIZED:
                return {CEvent::SResized {
                    .size = {ev.window.data1, ev.window.data2}
                }};
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                return {CEvent::SMouseButtonDown {
                    .button = static_cast<mouse::EButton>(ev.button.button),
                    .position = {ev.button.x, ev.button.y}
                }};
            case SDL_EVENT_MOUSE_BUTTON_UP:
                return {CEvent::SMouseButtonUp {
                    .button = static_cast<mouse::EButton>(ev.button.button),
                    .position = {ev.button.x, ev.button.y}
                }};
            case SDL_EVENT_MOUSE_MOTION:
                return {CEvent::SMouseMove {
                    .position = {ev.motion.x, ev.motion.y}
                }};
            case SDL_EVENT_KEY_DOWN:
                return {CEvent::SKeyDown {
                    .key = {
                        .code = ev.key.key,
                        .type = EKeyType::Keyboard
                    }
                }};
            case SDL_EVENT_KEY_UP:
                return {CEvent::SKeyUp {
                    .key = {
                        .code = ev.key.key,
                        .type = EKeyType::Keyboard
                    }
                }};
            default:
                break;
            }
        }

        return nullOpt;
    }

    const char* getTitle() noexcept
    {
        return SDL_GetWindowTitle(gWindowPtr);
    }

    SVector2i getPosition() noexcept
    {
        int x, y;

        if (!SDL_GetWindowPosition(gWindowPtr, &x, &y))
            return {};

        return {x, y};
    }

    SVector2u getSize() noexcept
    {
        int w, h;

        if (!SDL_GetWindowSize(gWindowPtr, &w, &h))
            return {};

        return {
            static_cast<SVector2u::ArithmeticType>(w),
            static_cast<SVector2u::ArithmeticType>(h)
        };
    }
}
