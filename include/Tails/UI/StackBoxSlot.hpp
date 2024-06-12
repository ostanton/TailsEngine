#ifndef TAILS_STACKBOXSLOT_HPP
#define TAILS_STACKBOXSLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/PanelSlot.hpp>

namespace tails
{
    class StackBox;

    struct TAILS_API Margin
    {
        float left, top, right, bottom;
    };

    enum class TAILS_API HorizontalAlignment
    {
        Fill,
        Left,
        Centre,
        Right
    };

    enum class TAILS_API VerticalAlignment
    {
        Fill,
        Top,
        Centre,
        Bottom
    };

    class TAILS_API StackBoxSlot : public PanelSlot
    {
    public:
        StackBoxSlot(PanelWidget* parent, std::unique_ptr<Widget> content);

        Margin padding;
        HorizontalAlignment horizontalAlignment;
        VerticalAlignment verticalAlignment;

        StackBox* getParentStackBox();

    protected:
        void tick(float deltaTime) override;
    };
}

#endif // TAILS_STACKBOXSLOT_HPP
