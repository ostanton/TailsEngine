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

    sf::FloatRect CSlot::getContentGlobalBounds() const
    {
        return m_slottedWidget.getGlobalBounds();
    }

    const sf::Transform& CSlot::getContentTransform() const
    {
        return m_slottedWidget.getTransform();
    }

    const sf::Transform& CSlot::getContentInverseTransform() const
    {
        return m_slottedWidget.getInverseTransform();
    }

    sf::FloatRect CSlot::getLocalBounds() const
    {
        if (getContent())
            return getContent()->getLocalBounds();
        
        return {};
    }

    void CSlot::drawContent(size_t index, sf::RenderStates& states)
    {
        if (getOwner())
            m_slottedWidget.setPosition(getOwner()->getPosition());
        states.transform *= m_slottedWidget.getTransform();
    }

    SSlottedWidget* CSlot::getSlottedWidgetAtIndex(const size_t index) const
    {
        if (auto const owner = getOwner())
        {
            if (auto const child = owner->getChildAt(index))
                return &child->getSlot()->m_slottedWidget;
        }
        
        return nullptr;
    }
    
    void CSlot::setContent(std::unique_ptr<CWidget> content)
    {
        content->m_slot = this;
        m_slottedWidget = std::move(content);
    }
}
