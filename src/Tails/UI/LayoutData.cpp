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
            std::move(widget),
            SLayoutData {
                {
                    transform.getPosition() + localOffset,
                    transform.getRotation(),
                    transform.getScale(),
                    transform.getOrigin()
                },
                localSize
            }
        };
    }

    SFloatRect SLayoutData::getRect() const noexcept
    {
        // TODO - account for rotation
        return {transform.getPosition(), size * transform.getScale()};
    }
}
