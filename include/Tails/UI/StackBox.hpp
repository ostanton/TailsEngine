#ifndef TAILS_STACKBOX_HPP
#define TAILS_STACKBOX_HPP

#include <Tails/UI/PanelWidget.hpp>

namespace tails
{
    class StackBoxSlot;

    enum class TAILS_API Orientation
    {
        Horizontal,
        Vertical
    };

    class TAILS_API StackBox : public PanelWidget
    {
    public:
        Orientation orientation;

        template<typename T>
        StackBoxSlot* addChildToStackBox()
        {
            return static_cast<StackBoxSlot*>(addChild<T>());
        }

        StackBoxSlot* addChildToStackBox(std::unique_ptr<Widget> content);
    };
}

#endif // TAILS_STACKBOX_HPP
