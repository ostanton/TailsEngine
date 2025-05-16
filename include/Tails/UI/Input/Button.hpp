#ifndef TAILS_BUTTON_WIDGET_HPP
#define TAILS_BUTTON_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/Delegates/MulticastDelegate.hpp>
#include <Tails/Templated/SharedRef.hpp>

namespace tails::ui
{
    class CButton;

    TAILS_DECLARE_MULTICAST_DELEGATE_VA_PARAMS(SOnButtonClicked, const TSharedRef<CButton>&);

    class TAILS_API CButton : public CWidget
    {
    protected:
        SOnButtonClicked m_onClicked;
        bool m_isPressed {false};
    };
}

#endif // TAILS_BUTTON_WIDGET_HPP
