#ifndef TAILS_CANVAS_PANEL_HPP
#define TAILS_CANVAS_PANEL_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Panel.hpp>
#include <Tails/UI/Children/PanelChildren.hpp>

namespace tails::ui
{
    class TAILS_API CCanvas final : public CPanel
    {
    public:
        struct TAILS_API SSlot final : SSlotBase
        {
            using SSlotBase::SSlotBase;

            SVector2f position;
            /** Whether to use the widget's desired size, or override it with the slot's size */
            bool useDesiredSize {true};
            SVector2f size;
        };

        CCanvas();

        [[nodiscard]] SVector2f getDesiredSize() const noexcept override;
        [[nodiscard]] IChildren& getChildren() noexcept override;
        void onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const override;

        [[nodiscard]] static SSlot* slotAsCanvasSlot(const std::shared_ptr<CWidget>& content) noexcept;

    private:
        std::unique_ptr<SSlotBase> makeSlot(std::shared_ptr<CWidget> content) override;

        TPanelChildren<SSlot> m_slots;
    };
}

#endif // TAILS_CANVAS_PANEL_HPP
