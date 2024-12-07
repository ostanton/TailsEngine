#include <Tails/UI/StackPanelSlot.hpp>
#include <Tails/UI/Panel.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails::ui
{
    void CStackPanelSlot::drawContent(const size_t index, sf::RenderStates& states)
    {
        const CSlot* lastSlot = nullptr;

        // if we are not the first child
        if (index > 0)
            lastSlot = getOwner()->getChildAt(index)->getSlot();

        if (lastSlot)
            m_slottedWidget.setPosition({
                getOwner()->getPosition().x + padding.left,
                lastSlot->getContentPosition().y + lastSlot->getLocalBounds().size.y + padding.top
            });
        else
            m_slottedWidget.setPosition({
                getOwner()->getPosition().x + padding.left,
                getOwner()->getPosition().y + padding.top
            });
        
        states.transform *= m_slottedWidget.getTransform();
    }

    sf::FloatRect CStackPanelSlot::getLocalBounds() const
    {
        if (!getContent()) return {};

        const auto globalBounds = getContentTransform().transformRect(getContent()->getLocalBounds());
        
        return {
            {
                globalBounds.position.x - padding.left,
                globalBounds.position.y - padding.top
            },
            {
                globalBounds.size.x + padding.right,
                globalBounds.size.y + padding.bottom
            }
        };
    }
}
