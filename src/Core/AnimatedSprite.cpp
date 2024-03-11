#include "TailsEngine/Core/AnimatedSprite.h"

tails::AnimatedSprite::AnimatedSprite()
{
    m_animationPlayer.setTargetSprite(this);
}

tails::AnimationPlayer& tails::AnimatedSprite::getAnimationPlayer()
{
    return m_animationPlayer;
}
