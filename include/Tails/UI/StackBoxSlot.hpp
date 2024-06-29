#ifndef TAILS_STACKBOXSLOT_HPP
#define TAILS_STACKBOXSLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/PanelSlot.hpp>
#include <Tails/UI/Layout/Margin.hpp>
#include <Tails/UI/Layout/Alignments.hpp>

namespace tails
{
    class StackBox;

    class TAILS_API StackBoxSlot : public PanelSlot
    {
    public:
        StackBoxSlot(PanelWidget* parent, std::unique_ptr<Widget> content);

        Margin padding;
        HorizontalAlignment horizontalAlignment {HorizontalAlignment::Fill};
        VerticalAlignment verticalAlignment {VerticalAlignment::Fill};

        StackBox* getParentStackBox();

    protected:
        void tick(float deltaTime) override;
    };
}

#endif // TAILS_STACKBOXSLOT_HPP
