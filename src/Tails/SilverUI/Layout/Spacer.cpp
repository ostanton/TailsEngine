#include <Tails/SilverUI/Layout/Spacer.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    SVector2f SSpacer::getMinimumSize() const noexcept
    {
        return desiredSize;
    }

    void SSpacer::onRender(IRenderer& renderer) const
    {
        const auto position = getPosition();
        const SFloatRect rect {
            position ? *position : SVector2f {},
            desiredSize
        };
        renderer.render(rect, debugColour);
    }
}
