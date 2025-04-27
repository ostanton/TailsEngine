#include <Tails/World/Components/AnimatedSpriteComponent.hpp>

namespace tails
{
    void CAnimatedSpriteComponent::onTick(const float deltaSeconds)
    {
        animationPlayer.tick(deltaSeconds);
    }

    void CAnimatedSpriteComponent::onRender(const CRenderer& renderer) const
    {
        animationPlayer.render(renderer, transform, tint);

        IComponent::onRender(renderer);
    }
}
