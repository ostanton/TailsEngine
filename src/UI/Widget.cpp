#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Slot.hpp>
#include <Tails/UI/PanelWidget.hpp>

namespace tails
{
    void Widget::removeFromParent()
    {
        getParent()->removeChild(this);
    }

    PanelWidget* Widget::getParent()
    {
        return slot->getParent();
    }
}
