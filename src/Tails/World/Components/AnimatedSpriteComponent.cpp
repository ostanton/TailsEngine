#include <Tails/World/Components/AnimatedSpriteComponent.hpp>

namespace tails
{
    SFloatRect CAnimatedSpriteComponent::getGlobalBounds() const noexcept
    {
        if (auto const currentAnim = animationPlayer.getPlayingAnimation())
            return {
                transform.position,
                transform.position + currentAnim->frames[currentAnim->currentFrame].bounds.size
            };

        return {transform.position, 0.f};
    }

    void CAnimatedSpriteComponent::onTick(const float deltaSeconds)
    {
        animationPlayer.tick(deltaSeconds);
    }

    void CAnimatedSpriteComponent::onRender(CRenderer& renderer) const
    {
        animationPlayer.render(renderer, transform, tint);
    }
}
