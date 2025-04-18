#ifndef TAILS_WINDOW_HPP
#define TAILS_WINDOW_HPP

#include <Tails/Core.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Templated/Optional.hpp>
#include <Tails/Input/Event.hpp>

struct SDL_Window;

namespace tails
{
    class CString;

    /**
     * OS-agnostic window
     *
     * TODO - should this be a widget, inherit from CCompoundWidget? If so, this basically becomes the
     * widget subsystem, as the root panel will be whatever the window's content widget is.
     * Would the window then remain as a renderer? Should the renderer be moved to not be an interface at all?
     */
    class TAILS_API CWindow : public IRenderer
    {
    public:
        CWindow(const CString& title, SVector2u size);
        CWindow(const CWindow&) = default;
        CWindow(CWindow&&) = default;
        CWindow& operator=(const CWindow&) = default;
        CWindow& operator=(CWindow&&) = default;
        ~CWindow() override;

        void close();
        TOptional<CEvent> pollEvent();

        [[nodiscard]] bool isOpen() const;
        
        void setTitle(const CString& title);
        [[nodiscard]] CString getTitle() const;

        void setPosition(SVector2i position);
        [[nodiscard]] SVector2i getPosition() const;

        void setSize(SVector2u size);
        [[nodiscard]] SVector2u getSize() const;

    private:
        SDL_Window* m_window {nullptr};
        bool m_open {true};
    };
}

#endif // TAILS_WINDOW_HPP
