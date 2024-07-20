#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Slot.hpp>
#include <Tails/UI/PanelWidget.hpp>
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
        // TODO
    }

    bool Widget::isFocused()
    {
        // TODO
        return false;
    }
}
