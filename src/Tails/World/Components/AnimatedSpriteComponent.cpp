#include <Tails/World/Components/AnimatedSpriteComponent.hpp>

namespace tails
{
    void CAnimatedSpriteComponent::onTick(const float deltaSeconds)
    {
        animationPlayer.tick(deltaSeconds);
    }

    void CAnimatedSpriteComponent::onRender() const
    {
        animationPlayer.render(transform, tint);

        IComponent::onRender();
    }
}
