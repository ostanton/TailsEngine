#ifndef TAILS_WIDGET_LAYOUT_DATA_HPP
#define TAILS_WIDGET_LAYOUT_DATA_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Transform2D.hpp>
#include <Tails/Maths/Rect.hpp>

#include <memory>

namespace tails::ui
{
    struct STransformedWidget;
    class CWidget;
    
    /**
     * Data representing a widget's current layout on the screen
     */
    struct TAILS_API SLayoutData final
    {
        /**
         * Makes a transformed widget to add to the CTransformedWidgets list object.
         * The offset is local, so if you want to use the current panel's position for the target widget,
         * pass in 0, as passing in the panel's position will offset it by that amount
         * @param widget Target widget
         * @param localOffset Local position offset
         * @param localSize Local widget size
         * @return Transformed widget for use in CTransformedWidgets
         */
        [[nodiscard]] STransformedWidget makeWidget(
            std::shared_ptr<CWidget> widget,
            SVector2f localOffset,
            SVector2f localSize
        ) const noexcept;

        /**
         * Gets the layout data as a rectangle, adjusted for its transform and size
         * @return Rectangle which this layout data occupies
         */
        [[nodiscard]] SFloatRect getRect() const noexcept;
        
        STransform2D transform;
        SVector2f size;
    };
}

#endif // TAILS_WIDGET_LAYOUT_DATA_HPP
