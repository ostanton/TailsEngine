#include <Tails/UI/PanelSlot.hpp>
#include <Tails/UI/Widget.hpp>

namespace tails
{
    PanelSlot::PanelSlot(PanelWidget* parent, std::unique_ptr<Widget> content)
        : Slot(parent, std::move(content))
    {

    }
}
