#ifndef TAILS_RECTENTITY_HPP
#define TAILS_RECTENTITY_HPP

#include <Tails/Entities/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace tails
{
    // replace with generic shape wrapper??
    class RectEntity final : public Entity
    {
    public:
        RectEntity()
        {
            m_rect.setSize(sf::Vector2f(64.f, 64.f));
            m_rect.setFillColor(sf::Color(255, 255, 255));
        }

        RectEntity* read(const nlohmann::json& json) override
        {
            return new RectEntity;
        }

        sf::RectangleShape& getRect() {return m_rect;}

    private:
        void tick(float deltaTime) override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::RectangleShape m_rect;
    };
}

#endif // TAILS_RECTENTITY_HPP
