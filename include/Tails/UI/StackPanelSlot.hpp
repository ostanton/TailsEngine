#ifndef TAILS_UI_STACK_PANEL_SLOT_HPP
#define TAILS_UI_STACK_PANEL_SLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Alignment.hpp>
#include <Tails/UI/Padding.hpp>

namespace tails::ui
{
    class TAILS_API CStackPanelSlot : public CSlot
    {
    public:
        EHorizontalAlignment hAlign {EHorizontalAlignment::Left};
        EVerticalAlignment vAlign {EVerticalAlignment::Top};
        SPadding padding;
        bool fill {false};

    private:
        void drawContent(size_t index, sf::RenderStates& states) override;

        sf::FloatRect getLocalBounds() const override;
    };
}

#endif // TAILS_UI_STACK_PANEL_SLOT_HPP
