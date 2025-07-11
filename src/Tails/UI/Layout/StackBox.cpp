#include <Tails/UI/Layout/StackBox.hpp>
#include <Tails/UI/Layout/Helpers.hpp>

namespace tails::ui
{
    CStackBox::CStackBox()
        : m_slots(this)
    {}

    SVector2f CStackBox::getDesiredSize() const noexcept
    {
        SVector2f size;
        for (const auto& slot : m_slots)
        {
            const auto& child = slot.content;
            const SVector2f childSize = child->getDesiredSize();

            switch (orientation)
            {
            case EOrientation::Vertical:
                size.x = maths::max(size.x, childSize.x + slot.margin.getSpaceAlong<EOrientation::Horizontal>());
                // TODO - max size?
                size.y += childSize.y + slot.margin.getSpaceAlong<EOrientation::Vertical>();
                break;
            case EOrientation::Horizontal:
                size.y = maths::max(size.y, childSize.y + slot.margin.getSpaceAlong<EOrientation::Vertical>());
                // TODO - max size?
                size.x += childSize.x + slot.margin.getSpaceAlong<EOrientation::Horizontal>();
                break;
            }
        }
        return size;
    }

    IChildren& CStackBox::getChildren() noexcept
    {
        return m_slots;
    }

    void CStackBox::onLayoutChildren(const SLayoutData& myLayout, CTransformedWidgets& transformedWidgets) const
    {
        if (orientation == EOrientation::Vertical)
            layoutChildrenInOrientation<EOrientation::Vertical>(m_slots, myLayout, transformedWidgets, 0.f);
        else
            layoutChildrenInOrientation<EOrientation::Horizontal>(m_slots, myLayout, transformedWidgets, 0.f);
    }

    CStackBox::SSlot* CStackBox::slotAsStackBoxSlot(const std::shared_ptr<CWidget>& content)
    {
        return dynamic_cast<SSlot*>(content->slot);
    }

    CStackBox::SSlot* CStackBox::addChildToStackBox(std::shared_ptr<CWidget>& content)
    {
        return dynamic_cast<SSlot*>(addChild(std::move(content)));
    }

    std::unique_ptr<SSlotBase> CStackBox::makeSlot(std::shared_ptr<CWidget> content)
    {
        return std::make_unique<SSlot>(this, std::move(content));
    }
}
