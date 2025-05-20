#include <Tails/UI/Layout/Spacer.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails::ui
{
    SVector2f CSpacer::getDesiredSize() const noexcept
    {
        return desiredSize;
    }

    void CSpacer::onPaint(const SLayoutData& myLayout, const float deltaSeconds) const
    {
        render::rect(myLayout.transform, myLayout.size, debugColour);
    }
}
