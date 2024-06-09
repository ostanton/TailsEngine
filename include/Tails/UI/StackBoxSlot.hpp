#ifndef TAILS_STACKBOXSLOT_HPP
#define TAILS_STACKBOXSLOT_HPP

#include <Tails/UI/PanelSlot.hpp>

namespace tails
{
    class StackBox;

    struct Margin
    {
        float left, top, right, bottom;
    };

    enum class HorizontalAlignment
    {
        Fill,
        Left,
        Centre,
        Right
    };

    enum class VerticalAlignment
    {
        Fill,
        Top,
        Centre,
        Bottom
    };

    class StackBoxSlot : public PanelSlot
    {
    public:
        StackBoxSlot(PanelWidget* parent, std::unique_ptr<Widget> content);

        Margin padding;
        HorizontalAlignment horizontalAlignment;
        VerticalAlignment verticalAlignment;

        StackBox* getParentStackBox();

    protected:
        void tick(float deltaTime);
    };
}

#endif // TAILS_STACKBOXSLOT_HPP
