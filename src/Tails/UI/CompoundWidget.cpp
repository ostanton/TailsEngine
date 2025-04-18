#include <Tails/UI/CompoundWidget.hpp>
#include <Tails/UI/TransformedWidgets.hpp>

namespace tails::ui
{
    CCompoundWidget::CCompoundWidget(std::shared_ptr<CWidget> content)
        : m_slot(this, std::move(content))
    {}

    SVector2f CCompoundWidget::getDesiredSize() const noexcept
    {
        if (const auto& content = m_slot.getContent())
        {
            if (content->visibility != EVisibility::Collapsed)
                return content->getDesiredSize();
        }

        return {};
    }

    IChildren& CCompoundWidget::getChildren() noexcept
    {
        return m_slot;
    }

    void CCompoundWidget::onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const
    {
        const auto& content = m_slot.getContent();
        
        if (!content)
            return;

        if (content->visibility == EVisibility::Collapsed)
            return;
        
        transformedWidgets.addWidget(myLayout.makeWidget(
            m_slot.getContent(),
            0.f,
            myLayout.size
        ));
    }

    void CCompoundWidget::onPaint(const SLayoutData& myLayout, const IRenderer& renderer, const float deltaSeconds) const
    {
        CTransformedWidgets widgets;
        onLayoutChildren(myLayout, widgets);

        if (widgets.size() == 0)
            return;
        
        const auto& [widget, layout] = widgets[0];
        
        if (widget->visibility == EVisibility::Hidden)
            return;
        
        widget->paint(layout, renderer, deltaSeconds);
    }
}
