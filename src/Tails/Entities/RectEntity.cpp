#include <Tails/Entities/RectEntity.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

namespace tails
{
    RectEntity* RectEntity::read(const nlohmann::json& json)
    {
        RectEntity* result {new RectEntity};
        result->m_rect.setFillColor(sf::Color(255, 0, 0));
        return result;
    }

    void RectEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_rect, states);
    }

    sf::FloatRect RectEntity::getGlobalBounds() const
    {
        return m_rect.getGlobalBounds();
    }
}
