#ifndef TAILS_WIDGET_HPP
#define TAILS_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/UI/Visibility.hpp>

#include <memory>

namespace tails::ui
{
    struct ISlot;
    struct SLayoutData;
    class CTransformedWidgets;
    struct IChildren;

    /**
     * Abstract base widget class. Has pure virtual functions for painting,
     * laying out potential children, etc.
     *
     * TODO - some way to traverse the widget hierarchy vertically, like Unreal's FWidgetPath
     */
    class TAILS_API CWidget : public std::enable_shared_from_this<CWidget>
    {
    public:
        CWidget() = default;
        CWidget(const CWidget&) = default;
        CWidget(CWidget&&) = default;
        CWidget& operator=(const CWidget&) = default;
        CWidget& operator=(CWidget&&) = default;
        virtual ~CWidget() = default;

        /**
         * This widget's desired size to draw at
         *
         * TODO - make this "calculateDesiredSize" instead, and cache it into a different "getDesiredSize" function?
         * That way each time we get the desired size, if we don't want to recalculate it (e.g. we're outside
         * a layout pass function) then we get the cached version from the last pass that was done.
         * 
         * @return Desired size
         */
        [[nodiscard]] virtual SVector2f getDesiredSize() const noexcept = 0;
        [[nodiscard]] virtual IChildren& getChildren() noexcept = 0;

        void paint(const SLayoutData& myLayout, float deltaSeconds);

        ISlot* slot {nullptr};
        EVisibility visibility {EVisibility::Visible};

    protected:
        virtual void onTick(float deltaSeconds);
        virtual void onLayoutChildren(
            const SLayoutData& myLayout,
            CTransformedWidgets& transformedWidgets
        ) const = 0;
        virtual void onPaint(const SLayoutData& myLayout, float deltaSeconds) const = 0;
    };
}

#endif // TAILS_WIDGET_HPP
