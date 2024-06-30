#ifndef TAILS_RECTENTITY_HPP
#define TAILS_RECTENTITY_HPP

#include <Tails/Config.hpp>
#include <Tails/Entities/Entity.hpp>

#include <SFML/Graphics/RectangleShape.hpp>

namespace tails
{
    // replace with generic shape wrapper??
    class TAILS_API RectEntity : public Entity
    {
    public:
        RectEntity()
        {
            m_rect.setSize(sf::Vector2f(64.f, 64.f));
            m_rect.setFillColor(sf::Color(255, 255, 255));
        }

        RectEntity* read(const nlohmann::json& json) override;

        sf::RectangleShape& getRect() {return m_rect;}

        sf::FloatRect getGlobalBounds() const override;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::RectangleShape m_rect;
    };
}

#endif // TAILS_RECTENTITY_HPP
