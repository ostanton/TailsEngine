#include <Tails/UI/Widget.hpp>

namespace tails::ui
{
    void CWidget::onTick(float deltaSeconds)
    {
    }

    void CWidget::paint(const SLayoutData& myLayout, const IRenderer& renderer, const float deltaSeconds)
    {
        onTick(deltaSeconds);
        onPaint(myLayout, renderer, deltaSeconds);
    }
}
