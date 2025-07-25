#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/TransformedWidgets.hpp>

namespace tails::ui
{
    STransformedWidget SLayoutData::makeWidget(
        std::shared_ptr<CWidget> widget,
        const SVector2f localOffset,
        const SVector2f localSize
    ) const noexcept
    {
        return {
            .widget = std::move(widget),
            .layoutData = {
                .transform = {
                    transform.getPosition() + localOffset,
                    transform.getRotation(),
                    transform.getScale(),
                    transform.getOrigin()
                },
                .size = localSize
            }
        };
    }

    SFloatOrientedRect SLayoutData::getRect() const noexcept
    {
        return transform.getMatrix().transformToOrientedRect({
            .position = transform.getPosition(),
            .size = size * transform.getScale(),
        });
    }
}
