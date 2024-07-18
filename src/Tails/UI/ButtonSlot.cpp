#include <Tails/UI/ButtonSlot.hpp>
#include <Tails/UI/Widget.hpp>

namespace tails
{
    ButtonSlot::ButtonSlot(PanelWidget* parent, std::unique_ptr<Widget> content) : PanelSlot(parent, std::move(content))
    {

    }
} // tails
