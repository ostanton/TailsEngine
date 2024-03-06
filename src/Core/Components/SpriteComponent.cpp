#include "TailsEngine/Core/Components/SpriteComponent.h"

#include <SFML/Graphics/RenderTarget.hpp>

void tails::SpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

sf::FloatRect tails::SpriteComponent::getLocalBounds()
{
    return m_sprite.getLocalBounds();
}

sf::FloatRect tails::SpriteComponent::getGlobalBounds()
{
    return getTransform().transformRect(m_sprite.getGlobalBounds());
}

sf::Sprite& tails::SpriteComponent::getSprite()
{
    return m_sprite;
}
