#include <Tails/Window.hpp>
#include <Tails/String.hpp>

#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

namespace tails
{
    CWindow::CWindow(const CString& title, const SVector2u size)
        : m_window(SDL_CreateWindow(
            title.getData(),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            SDL_WINDOW_RESIZABLE))
    {
        if (!m_window)
        {
            close();
            SDL_DestroyWindow(m_window);
            return;
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer)
        {
            close();
            SDL_DestroyWindow(m_window);
            return;
        }
    }

    CWindow::~CWindow()
    {
        close();
        SDL_DestroyWindow(m_window);
    }

    void CWindow::close()
    {
        m_open = false;
    }

    TOptional<CEvent> CWindow::pollEvent()
    {
        // TODO - PSP home button doesn't work for some reason!
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
                return CEvent {CEvent::SClosed {}};
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                return CEvent {CEvent::SMouseButtonDown {
                    static_cast<mouse::EButton>(ev.button.button),
                    {ev.button.x, ev.button.y}
                }};
            default:
                break;
            }
        }
        return nullOpt;
    }

    bool CWindow::isOpen() const
    {
        return m_open;
    }

    void CWindow::setTitle(const CString& title)
    {
        SDL_SetWindowTitle(m_window, title.getData());
    }

    CString CWindow::getTitle() const
    {
        return SDL_GetWindowTitle(m_window);
    }

    void CWindow::setPosition(const SVector2i position)
    {
        SDL_SetWindowPosition(m_window, position.x, position.y);
    }

    SVector2i CWindow::getPosition() const
    {
        SVector2i position;
        SDL_GetWindowPosition(m_window, &position.x, &position.y);
        return position;
    }

    void CWindow::setSize(const SVector2u size)
    {
        SDL_SetWindowSize(m_window, static_cast<int>(size.x), static_cast<int>(size.y));
    }

    SVector2u CWindow::getSize() const
    {
        SVector2i size;
        SDL_GetWindowSize(m_window, &size.x, &size.y);
        return SVector2u {size};
    }
}
