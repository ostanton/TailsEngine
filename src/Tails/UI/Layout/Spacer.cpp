#include <Tails/UI/Layout/Spacer.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails::ui
{
    SVector2f CSpacer::getDesiredSize() const noexcept
    {
        return desiredSize;
    }

    void CSpacer::onPaint(const SLayoutData& myLayout, const CRenderer& renderer, const float deltaSeconds) const
    {
        renderer.render(myLayout.transform, myLayout.size, debugColour);
    }
}
