#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "AnimationPlayer.h"
#include "Obj.h"

namespace tails
{
class AnimatedSprite final : public Object, public sf::Sprite
{
public:
    AnimatedSprite();
    
    AnimationPlayer& getAnimationPlayer();

    bool isAnimated {true};

private:
    AnimationPlayer m_animationPlayer;
};

}
