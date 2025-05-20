#ifndef TAILS_LEAF_WIDGET_HPP
#define TAILS_LEAF_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Widget.hpp>
#include <Tails/UI/Children/NoChildren.hpp>

namespace tails::ui
{
    /**
     * An abstract widget class specifically with no children
     */
    class TAILS_API CLeafWidget : public CWidget
    {
    public:
        CLeafWidget();
        
        [[nodiscard]] SVector2f getDesiredSize() const noexcept override = 0;
        [[nodiscard]] IChildren& getChildren() noexcept override;
        void onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const override;
        void onPaint(const SLayoutData& myLayout, float deltaSeconds) const override = 0;

    private:
        SNoChildren m_noChildren;
    };
}

#endif // TAILS_LEAF_WIDGET_HPP
