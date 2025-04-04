#include <Tails/SilverUI/Layout/StackBox.hpp>

namespace tails
{
    std::unique_ptr<ISlot> SStackBox::makeSlot(std::shared_ptr<SWidget> content)
    {
        return std::make_unique<CStackBoxSlot>(this, std::move(content));
    }
}
