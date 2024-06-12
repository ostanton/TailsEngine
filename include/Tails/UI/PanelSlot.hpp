#ifndef TAILS_PANELSLOT_HPP
#define TAILS_PANELSLOT_HPP

#include <Tails/UI/Slot.hpp>

namespace tails
{
    class PanelWidget;

    class TAILS_API PanelSlot : public Slot
    {
        friend PanelWidget;

    public:
        PanelSlot(PanelWidget* parent, std::unique_ptr<Widget> content);
    };
}

#endif // TAILS_PANELSLOT_HPP
