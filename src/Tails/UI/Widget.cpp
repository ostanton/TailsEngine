#include <Tails/UI/Widget.hpp>

namespace tails::ui
{
    void CWidget::onTick(float deltaSeconds)
    {
    }

    void CWidget::paint(const SLayoutData& myLayout, const float deltaSeconds)
    {
        onTick(deltaSeconds);
        onPaint(myLayout, deltaSeconds);
    }
}
