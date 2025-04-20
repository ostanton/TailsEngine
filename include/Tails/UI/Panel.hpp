#ifndef TAILS_PANEL_WIDGET_HPP
#define TAILS_PANEL_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Slot.hpp>

#include <vector>
#include <memory>

namespace tails::ui
{
    class TAILS_API CPanel : public CWidget
    {
    public:
        CPanel() = default;
        CPanel(const CPanel&) = delete;
        CPanel(CPanel&&) = default;
        CPanel& operator=(const CPanel&) = delete;
        CPanel& operator=(CPanel&&) = default;
        ~CPanel() override;

        [[nodiscard]] SVector2f getDesiredSize() const noexcept override = 0;
        [[nodiscard]] IChildren& getChildren() noexcept override = 0;
        
        template<typename T>
        ISlot* addChild()
        {
            return addChild(std::make_shared<T>());
        }
        
        ISlot* addChild(std::shared_ptr<CWidget> content);
        void clearChildren();

        void onLayoutChildren(
            const SLayoutData& myLayout,
            CTransformedWidgets& transformedWidgets
        ) const override = 0;
        
    protected:
        void onPaint(const SLayoutData& myLayout, const CRenderer& renderer, float deltaSeconds) const override;
        
        virtual std::unique_ptr<ISlot> makeSlot(std::shared_ptr<CWidget> content) = 0;
    };
}

#endif // TAILS_PANEL_WIDGET_HPP
