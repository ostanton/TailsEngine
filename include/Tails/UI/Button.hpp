#ifndef TAILS_BUTTON_HPP
#define TAILS_BUTTON_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/PanelWidget.hpp>
#include <Tails/Events/MultiEvent.hpp>

namespace tails
{
    class ButtonSlot;

    class TAILS_API Button : public PanelWidget
    {
    public:
        template<typename T>
        ButtonSlot* addChildToButton()
        {
            return static_cast<ButtonSlot*>(addChild<T>());
        }

        ButtonSlot* addChildToButton(std::unique_ptr<Widget> content);

        MultiEvent<Button*> clickEvent;
        MultiEvent<Button*> hoverEvent;
        MultiEvent<Button*> unHoverEvent;
        MultiEvent<Button*> pressEvent;
        MultiEvent<Button*> releaseEvent;

        inline bool isPressed() const {return m_pressed;}
        inline bool isHovered() const {return m_hovered;}

    protected:
        void tick(float deltaTime) override;

    private:
        bool m_pressed {false}; // is currently pressed
        bool m_hovered {false}; // is currently hovered
    };

} // tails

#endif //TAILS_BUTTON_HPP
