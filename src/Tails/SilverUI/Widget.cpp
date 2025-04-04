#include <Tails/SilverUI/Widget.hpp>
#include <Tails/SilverUI/Slot.hpp>

namespace tails
{
    SVector2f SWidget::getMinimumSize() const noexcept
    {
        return {};
    }

    TOptional<SVector2f> SWidget::getPosition() const noexcept
    {
        if (!m_slot)
            return nullOpt;

        return m_slot->getPosition();
    }

    void SWidget::onTick(float deltaSeconds)
    {
        
    }
}
