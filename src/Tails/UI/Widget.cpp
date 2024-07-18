#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Slot.hpp>
#include <Tails/UI/PanelWidget.hpp>
#include <Tails/Layers/ScreenLayer.hpp>
#include <Tails/UI/WidgetNavigation.hpp>

namespace tails
{
    void Widget::removeFromParent()
    {
        if (getParent())
            getParent()->removeChild(this);
    }

    PanelWidget* Widget::getParent() const
    {
        if (!slot) return nullptr;

        return slot->getParent();
    }

    void Widget::setFocus()
    {
        auto screen = getTypedOuter<ScreenLayer>();
        screen->getNavigation().setFocus(this);
    }

    bool Widget::isFocused()
    {
        return getTypedOuter<ScreenLayer>()->getNavigation().widgetHasFocus(this);
    }
}
