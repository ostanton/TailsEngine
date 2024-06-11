#include <Tails/Entities/RectEntity.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    void RectEntity::tick(float deltaTime)
    {
        setPosition(getPosition().x + deltaTime * 4.f, 0);

        if (getPosition().x >= 24.f)
        {
            destroy();
        }
    }

    void RectEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_rect, states);
    }
}
