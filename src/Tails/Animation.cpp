#include <Tails/Animation.hpp>
#include <Tails/String.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Renderer/Renderer.hpp>

namespace tails
{
    SAnimationPlayer::SAnimationPlayer(const CString& spriteSheetPath)
        : spriteSheet(assets::loadAsset<CTexture>(spriteSheetPath))
    {}

    SAnimationPlayer::SAnimationPlayer(std::shared_ptr<CTexture> inSpriteSheet)
        : spriteSheet(std::move(inSpriteSheet))
    {}

    void SAnimationPlayer::addAnimation(const std::string_view name, SAnimation animation)
    {
        animations[name] = std::move(animation);
    }

    SAnimation* SAnimationPlayer::getAnimation(const std::string_view name) noexcept
    {
        if (!containsAnimation(name))
            return nullptr;

        return &animations[name];
    }

    const SAnimation* SAnimationPlayer::getAnimation(const std::string_view name) const noexcept
    {
        if (!containsAnimation(name))
            return nullptr;
        
        return &animations.at(name);
    }

    bool SAnimationPlayer::containsAnimation(const std::string_view name) const noexcept
    {
        return animations.contains(name);
    }

    void SAnimationPlayer::playAnimation(const std::string_view name) noexcept
    {
        if (!containsAnimation(name))
            return;

        playingAnimation = name;
    }

    SAnimation* SAnimationPlayer::getPlayingAnimation() noexcept
    {
        return getAnimation(playingAnimation);
    }

    const SAnimation* SAnimationPlayer::getPlayingAnimation() const noexcept
    {
        return getAnimation(playingAnimation);
    }

    bool SAnimationPlayer::removeAnimation(const std::string_view name) noexcept
    {
        if (!containsAnimation(name))
            return false;

        animations.erase(name);
        return true;
    }

    void SAnimationPlayer::tick(const float deltaSeconds)
    {
        auto const currentAnim = getPlayingAnimation();
        if (!currentAnim)
            return;

        // we've reached the end of a non-looping animation
        if (currentAnim->currentFrame >= currentAnim->frames.size())
            return;

        // TODO - use frames per seconds here instead of just numbers!
        const float playRate {
            static_cast<float>(currentAnim->frameRate) * currentAnim->frames[currentAnim->currentFrame].playRate
        };
        currentTime += deltaSeconds * playRate;

        // we haven't reached the next frame yet
        if (currentTime < 1.f / playRate)
            return;

        currentAnim->currentFrame++;

        if (currentAnim->currentFrame >= currentAnim->frames.size())
        {
            if (currentAnim->loop)
                currentAnim->currentFrame = 0;
        }

        currentTime = 0.f;
    }

    void SAnimationPlayer::render(
        const CRenderer& renderer,
        const STransform2D& transform,
        const SColour colour
    ) const
    {
        if (!spriteSheet)
            return;

        if (auto const currentAnim = getPlayingAnimation())
        {
            const auto& bounds = currentAnim->frames[currentAnim->currentFrame].bounds;
            renderer.render(
                spriteSheet,
                bounds,
                transform,
                SVector2f {bounds.size},
                colour
            );
        }
        else
        {
            renderer.render(spriteSheet, transform, {}, colour);
        }
    }
}
