#ifndef TAILS_BUTTONSLOT_HPP
#define TAILS_BUTTONSLOT_HPP

#include <Tails/UI/PanelSlot.hpp>

namespace tails
{
    class Button;

    class ButtonSlot : public PanelSlot
    {
        friend Button;

    public:
        ButtonSlot(PanelWidget* parent, std::unique_ptr<Widget> content);
    };

} // tails

#endif //TAILS_BUTTONSLOT_HPP
