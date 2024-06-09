#include <Tails/UI/StackBoxSlot.hpp>
#include <Tails/UI/Widget.hpp>

namespace tails
{
    StackBoxSlot::StackBoxSlot(PanelWidget* parent, std::unique_ptr<Widget> content)
        : PanelSlot(parent, std::move(content))
    {

    }
}
