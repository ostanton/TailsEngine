#include <Tails/UI/StackPanelSlot.hpp>
#include <Tails/UI/Panel.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails::ui
{
    void CStackPanelSlot::drawContent(const size_t index, sf::RenderStates& states)
    {
        // we don't need to offset by our owner's position as the incoming states already have that
        if (index > 0)
        {
            const CSlot* lastSlot = getOwner()->getChildAt(index)->getSlot();
            m_slottedWidget.setPosition({
                padding.left,
                lastSlot->getContentGlobalBounds().size.y + padding.top
            });
        }
        else
        {
            m_slottedWidget.setPosition({
                padding.left,
                padding.top
            });
        }

        states.transform *= m_slottedWidget.getTransform();
    }

    sf::FloatRect CStackPanelSlot::getLocalBounds() const
    {
        if (!getContent()) return {};

        const auto localBounds = getContent()->getLocalBounds();
        
        return {
            {
                localBounds.position.x - padding.left,
                localBounds.position.y - padding.top
            },
            {
                localBounds.size.x + padding.right,
                localBounds.size.y + padding.bottom
            }
        };
    }
}
