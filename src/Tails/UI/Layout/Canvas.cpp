#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/TransformedWidgets.hpp>

#include "Tails/UI/Rendering/DrawElementList.hpp"

namespace tails::ui
{
    CCanvas::CCanvas()
        : m_slots(this)
    {}

    SVector2f CCanvas::getDesiredSize() const noexcept
    {
        SVector2f size;
        for (const auto& slot : m_slots)
        {
            const auto& child = slot.content;
            const SVector2f childSize = slot.useDesiredSize ? child->getDesiredSize() : slot.size;
            size.x = maths::max(size.x, childSize.x + slot.position.x);
            size.y = maths::max(size.y, childSize.y + slot.position.y);
        }
        return size;
    }

    IChildren& CCanvas::getChildren() noexcept
    {
        return m_slots;
    }

    void CCanvas::onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const
    {
        for (const auto& slot : m_slots)
        {
            const auto& child = slot.content;
            const SVector2f childSize = slot.useDesiredSize ? child->getDesiredSize() : slot.size;
            transformedWidgets.addWidget(myLayout.makeWidget(child, slot.position, childSize));
        }
    }

    CCanvas::SSlot* CCanvas::slotAsCanvasSlot(const std::shared_ptr<CWidget>& content) noexcept
    {
        return dynamic_cast<SSlot*>(content->slot);
    }

    std::unique_ptr<SSlotBase> CCanvas::makeSlot(std::shared_ptr<CWidget> content)
    {
        return std::make_unique<SSlot>(this, std::move(content));
    }
}
