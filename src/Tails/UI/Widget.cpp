#include <Tails/UI/Widget.hpp>
#include <Tails/Engine.hpp>
#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Panel.hpp>
#include <Tails/UI/UISubsystem.hpp>

namespace tails::ui
{
    CEngine& CWidget::getEngine() const
    {
        return *getTypedOuter<CEngine>();
    }

    CPanel* CWidget::getParent() const
    {
        return getTypedOuter<CPanel>();
    }

    CSlot* CWidget::getSlot() const
    {
        return m_slot;
    }

    void CWidget::focus()
    {
        getEngine().getUISubsystem().focusWidget(this);
    }

    void CWidget::destroy()
    {
        markForDestroy();
    }

    sf::Vector2f CWidget::getPosition() const
    {
        if (!getSlot()) return {};

        return getSlot()->getContentPosition(); // TODO - take into account additive transform with these!
    }

    sf::Angle CWidget::getRotation() const
    {
        if (!getSlot()) return {};

        return getSlot()->getContentRotation();
    }

    sf::Vector2f CWidget::getScale() const
    {
        if (!getSlot()) return {};

        return getSlot()->getContentScale();
    }

    std::optional<std::reference_wrapper<const sf::Transform>> CWidget::getTransform() const
    {
        if (!getSlot()) return std::nullopt;

        return std::ref(getSlot()->getContentTransform());
    }

    std::optional<std::reference_wrapper<const sf::Transform>> CWidget::getInverseTransform() const
    {
        if (!getSlot()) return std::nullopt;

        return std::ref(getSlot()->getContentInverseTransform());
    }

    sf::FloatRect CWidget::getLocalBounds() const
    {
        return {};
    }
}
