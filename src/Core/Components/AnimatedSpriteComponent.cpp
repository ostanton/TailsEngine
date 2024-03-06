#include "TailsEngine/Core/Components/AnimatedSpriteComponent.h"

#include <SFML/Graphics/RenderTarget.hpp>

void tails::AnimatedSpriteComponent::create()
{
    Component::create();

    m_animationPlayer.setTargetSprite(&m_sprite);
}

void tails::AnimatedSpriteComponent::update(float deltaTime)
{
    Component::update(deltaTime);

    m_animationPlayer.update(deltaTime);
}

void tails::AnimatedSpriteComponent::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

sf::FloatRect tails::AnimatedSpriteComponent::getLocalBounds()
{
    return m_sprite.getLocalBounds();
}

sf::FloatRect tails::AnimatedSpriteComponent::getGlobalBounds()
{
    return getTransform().transformRect(m_sprite.getLocalBounds());
}

tails::AnimationPlayer& tails::AnimatedSpriteComponent::getAnimationPlayer()
{
    return m_animationPlayer;
}

sf::Sprite& tails::AnimatedSpriteComponent::getSprite()
{
    return m_sprite;
}
