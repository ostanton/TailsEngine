#include <Tails/UI/Panel.hpp>
#include <Tails/UI/TransformedWidgets.hpp>
#include <Tails/UI/Children/Children.hpp>

namespace tails::ui
{
    CPanel::~CPanel() = default;

    SSlotBase* CPanel::addChild(std::shared_ptr<CWidget> content)
    {
        return getChildren().addChild(std::move(content));
    }

    void CPanel::clearChildren()
    {
        getChildren().clearChildren();
    }

    void CPanel::onPaint(
        const SLayoutData& myLayout,
        CDrawElementList& drawElements,
        const float deltaSeconds
    ) const
    {
        CTransformedWidgets widgets;
        onLayoutChildren(myLayout, widgets);
        
        for (const auto& [widget, layoutData] : widgets)
        {
            if (widget->visibility != EVisibility::Visible)
                continue;
            
            widget->paint(layoutData, drawElements, deltaSeconds);
        }
    }
}
