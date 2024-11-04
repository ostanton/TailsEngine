#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Panel.hpp>

namespace tails::ui
{
    CSlot::CSlot() = default;
    CSlot::CSlot(CSlot&&) noexcept = default;
    CSlot& CSlot::operator=(CSlot&&) noexcept = default;
    CSlot::~CSlot() = default;

    CPanel* CSlot::getOwner() const
    {
        return getTypedOuter<CPanel>();
    }

    void CSlot::setContent(std::unique_ptr<CWidget> content)
    {
        m_content = std::move(content);
        m_content->outer = this;
    }
}
