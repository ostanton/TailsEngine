#include <Tails/UI/StackPanelSlot.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails::ui
{
    void CStackPanelSlot::drawContent(const size_t index, sf::RenderStates& states)
    {
        CSlot::drawContent(index, states);
    }
}
