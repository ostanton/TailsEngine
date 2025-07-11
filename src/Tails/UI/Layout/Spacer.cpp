#include <Tails/UI/Layout/Spacer.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/UI/Rendering/DrawElementList.hpp>

namespace tails::ui
{
    SVector2f CSpacer::getDesiredSize() const noexcept
    {
        return desiredSize;
    }

    void CSpacer::onPaint(
        const SLayoutData& myLayout,
        CDrawElementList& drawElements,
        const float deltaSeconds
    ) const
    {
        drawElements.add(myLayout, debugColour);
        //render::rect(myLayout.transform, myLayout.size, debugColour);
    }
}
