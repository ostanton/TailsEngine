#include <Tails/UI/StackPanelSlot.hpp>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transformable.hpp>

namespace tails::ui
{
    void CStackPanelSlot::drawContent(size_t index, sf::RenderStates& states)
    {
        sf::Transformable transform;
        states.transform *= transform.getTransform();
    }
}
