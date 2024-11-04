#include <Tails/UI/Widget.hpp>
#include <Tails/Engine.hpp>
#include <Tails/UI/Slot.hpp>

namespace tails::ui
{
    CEngine& CWidget::getEngine() const
    {
        return *getTypedOuter<CEngine>();
    }

    CPanel* CWidget::getParent() const
    {
        if (const auto slot = getSlot())
            return slot->getOwner();
        
        return nullptr;
    }

    CSlot* CWidget::getSlot() const
    {
        return getTypedOuter<CSlot>();
    }

    void CWidget::destroy()
    {
        markForDestroy();
    }
}
