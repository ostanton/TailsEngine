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
                    transform.position + localOffset,
                    transform.rotation,
                    transform.scale2D
                },
                localSize
            }
        };
    }

    SFloatRect SLayoutData::getRect() const noexcept
    {
        return {transform.position, size};
    }
}
