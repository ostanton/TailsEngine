#include <Tails/UI/Widget.hpp>
#include <Tails/Engine.hpp>
#include <Tails/UI/Slot.hpp>

namespace tails::ui
{
    CEngine& CWidget::getEngine() const
    {
        return *getTypedOuter<CEngine>();
    }

    CPanel* CWidget::getParent() const
    {
        if (const auto slot = getSlot())
            return slot->getOwner();
        
        return nullptr;
    }

    CSlot* CWidget::getSlot() const
    {
        return getTypedOuter<CSlot>();
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
