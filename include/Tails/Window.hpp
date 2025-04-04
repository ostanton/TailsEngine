#ifndef TAILS_WINDOW_HPP
#define TAILS_WINDOW_HPP

#include <Tails/Core.hpp>
#include <Tails/Input/EventPoller.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Maths/Vector2.hpp>

struct SDL_Window;

namespace tails
{
    class CString;

    struct TAILS_API SMessageBoxButton
    {
        const char* text;
    };
    
    /**
     * OS-agnostic window
     */
    class TAILS_API CWindow : public IEventPoller, public IRenderer
    {
    public:
        CWindow(const CString& title, SVector2u size);
        ~CWindow() override;

        void close();
        TOptional<CEvent> pollEvent() override;

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
