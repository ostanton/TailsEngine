#include <Tails/RectEntity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void RectEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_rect, states);
    }
}
