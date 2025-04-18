#ifndef TAILS_STACK_BOX_WIDGET_HPP
#define TAILS_STACK_BOX_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Panel.hpp>
#include <Tails/UI/Alignment.hpp>
#include <Tails/UI/Orientation.hpp>
#include <Tails/UI/Children/PanelChildren.hpp>
#include <Tails/UI/Margin.hpp>

namespace tails::ui
{
    class TAILS_API CStackBox final : public CPanel
    {
    public:
        struct TAILS_API SSlot final : ISlot
        {
            using ISlot::ISlot;
            
            EHorizontalAlignment hAlign;
            EVerticalAlignment vAlign;
            SMargin margin;
        };

        CStackBox();

        [[nodiscard]] SVector2f getDesiredSize() const noexcept override;
        IChildren& getChildren() noexcept override;
        void onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const override;

        static SSlot* slotAsStackBoxSlot(const std::shared_ptr<CWidget>& content);

        SSlot* addChildToStackBox(std::shared_ptr<CWidget>& content);

        EOrientation orientation {EOrientation::Vertical};

    private:
        std::unique_ptr<ISlot> makeSlot(std::shared_ptr<CWidget> content) override;

        TPanelChildren<SSlot> m_slots;
    };
}

#endif // TAILS_STACK_BOX_WIDGET_HPP
