#include <Tails/UI/StackBox.hpp>
#include <Tails/UI/StackBoxSlot.hpp>

namespace tails
{
    StackBoxSlot* StackBox::addChildToStackBox(std::unique_ptr<Widget> content)
    {
        return addChild<StackBoxSlot>(std::move(content));
    }
}
