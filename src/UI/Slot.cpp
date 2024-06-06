#include <Tails/UI/Slot.hpp>
#include <Tails/UI/Widget.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void Slot::tick(float deltaTime)
    {
        content->tick(deltaTime);
    }

    void Slot::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(*content, states);
    }
}
