#ifndef TAILS_COMPOUND_WIDGET_HPP
#define TAILS_COMPOUND_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Children/SingleChildren.hpp>
#include <Tails/UI/Slot.hpp>

namespace tails::ui
{
    /**
     * As opposed to CPanel and CLeafWidget, CCompoundWidget has a single child, and is generally meant for
     * composing new widgets like menus and such
     */
    class TAILS_API CCompoundWidget : public CWidget
    {
    public:
        struct SSlot : ISlot
        {
            using ISlot::ISlot;
        };

        CCompoundWidget();

        [[nodiscard]] SVector2f getDesiredSize() const noexcept override;
        [[nodiscard]] IChildren& getChildren() noexcept override;

        void onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const override;

        void setContent(std::shared_ptr<CWidget> content);
        
    protected:
        void onPaint(const SLayoutData& myLayout, float deltaSeconds) const override;

        TSingleChildren<SSlot> m_slot;
    };
}

#endif // TAILS_COMPOUND_WIDGET_HPP
