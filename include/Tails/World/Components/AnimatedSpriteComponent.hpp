#ifndef TAILS_ANIMATED_SPRITE_COMPONENT_HPP
#define TAILS_ANIMATED_SPRITE_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/Animation.hpp>

namespace tails
{
    /**
     * Component wrapper for an SAnimationPlayer
     */
    class TAILS_API CAnimatedSpriteComponent : public IComponent
    {
    public:
        SAnimationPlayer animationPlayer;
        SColour tint;

    protected:
        void onTick(float deltaSeconds) override;
        void onRender(const CRenderer& renderer) const override;
    };
}

#endif // TAILS_ANIMATED_SPRITE_COMPONENT_HPP
