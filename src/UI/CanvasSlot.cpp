#include <Tails/UI/CanvasSlot.hpp>
#include <Tails/UI/Widget.hpp>

namespace tails
{
    CanvasSlot::CanvasSlot(PanelWidget* parent, std::unique_ptr<Widget> content)
        : PanelSlot(parent, std::move(content))
    {

    }
} // tails
