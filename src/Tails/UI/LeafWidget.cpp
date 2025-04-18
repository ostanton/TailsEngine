#include <Tails/UI/LeafWidget.hpp>

namespace tails::ui
{
    CLeafWidget::CLeafWidget()
        : m_noChildren(this)
    {}

    IChildren& CLeafWidget::getChildren() noexcept
    {
        return m_noChildren;
    }

    void CLeafWidget::onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const
    {
        // nothing!
    }
}
