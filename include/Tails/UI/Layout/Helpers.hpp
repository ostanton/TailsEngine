#ifndef TAILS_LAYOUT_HELPERS_HPP
#define TAILS_LAYOUT_HELPERS_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Children/PanelChildren.hpp>
#include <Tails/UI/Orientation.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/TransformedWidgets.hpp>

namespace tails::ui
{
    template<EOrientation Orientation, typename SlotT>
    void layoutChildrenInOrientation(
        const TPanelChildren<SlotT>& children,
        const SLayoutData& layoutData,
        CTransformedWidgets& transformedWidgets,
        const float offset
    )
    {
        if (children.size() == 0)
            return;

        float totalOffset {0.f};
        for (const auto& slot : children)
        {
            const auto& child = slot.content;

            float childSize {0.f};
            if (child->visibility != EVisibility::Collapsed)
            {
                const SVector2f childDesiredSize {child->getDesiredSize()};
                childSize = Orientation == EOrientation::Vertical ? childDesiredSize.y : childDesiredSize.x;
            }

            const SMargin margin {slot.margin};
            SVector2f localSize {
                Orientation == EOrientation::Vertical ?
                    SVector2f {layoutData.size.x, childSize} :
                    SVector2f {childSize, layoutData.size.y}
            };
            SVector2f localPosition {
                Orientation == EOrientation::Vertical ?
                    SVector2f {0.f, totalOffset + offset + margin.top} :
                    SVector2f {totalOffset + offset + margin.left, 0.f}
            };

            transformedWidgets.addWidget(layoutData.makeWidget(child, localPosition, localSize));
            
            if (child->visibility != EVisibility::Collapsed)
                totalOffset +=
                    (Orientation == EOrientation::Vertical ? localSize.y : localSize.x) +
                    (Orientation == EOrientation::Vertical ? margin.getHeight() : margin.getWidth());
        }
    }
}

#endif // TAILS_LAYOUT_HELPERS_HPP
