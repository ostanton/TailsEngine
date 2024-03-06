#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "PrimitiveComponent.h"

namespace tails
{
class SpriteComponent : public PrimitiveComponent
{
public:
    sf::FloatRect getLocalBounds() override;
    sf::FloatRect getGlobalBounds() override;

    sf::Sprite& getSprite();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
};

}
