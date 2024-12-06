#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Panel.hpp>

#include <SFML/Graphics/RenderStates.hpp>

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

    sf::Vector2f CSlot::getContentPosition() const
    {
        return m_slottedWidget.getPosition();
    }

    sf::Angle CSlot::getContentRotation() const
    {
        return m_slottedWidget.getRotation();
    }

    sf::Vector2f CSlot::getContentScale() const
    {
        return m_slottedWidget.getScale();
    }

    const sf::Transform& CSlot::getContentTransform() const
    {
        return m_slottedWidget.getTransform();
    }

    const sf::Transform& CSlot::getContentInverseTransform() const
    {
        return m_slottedWidget.getInverseTransform();
    }

    void CSlot::drawContent(size_t index, sf::RenderStates& states)
    {
        if (getOwner())
            m_slottedWidget.setPosition(getOwner()->getPosition());
        states.transform *= m_slottedWidget.getTransform();
    }

    void CSlot::setContent(std::unique_ptr<CWidget> content)
    {
        m_slottedWidget = std::move(content);
        m_slottedWidget->outer = this;
    }
}
