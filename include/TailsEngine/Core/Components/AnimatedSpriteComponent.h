#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "PrimitiveComponent.h"
#include "TailsEngine/Core/AnimationPlayer.h"

namespace tails
{
class AnimatedSpriteComponent : public PrimitiveComponent
{
public:
    sf::FloatRect getLocalBounds() override;
    sf::FloatRect getGlobalBounds() override;
    
    AnimationPlayer& getAnimationPlayer();
    sf::Sprite& getSprite();

protected:
    void create() override;
    void update(float deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Sprite m_sprite;
    AnimationPlayer m_animationPlayer;
};

}
