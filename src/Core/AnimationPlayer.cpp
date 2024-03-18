#include "TailsEngine/Core/AnimationPlayer.h"

#include <ranges>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TailsEngine/Debug/Debug.h"

void tails::AnimationInfo::setupFrames(unsigned frameAmount)
{
    // Create the frames of the animation from the sprite sheet and cell size
    //const sf::Vector2u cellsInSheet {
    //    owningPlayer->getTargetSprite().getTexture()->getSize().x / cellSize.x,
    //    owningPlayer->getTargetSprite().getTexture()->getSize().y / cellSize.y
    //};
    
    for (unsigned i {0}; i < frameAmount; i++)
    {
        FrameInfo frameInfo;
        // Set cell size. If i != 0 (>), we add our cell size and multiple by i to get the left position
        const sf::IntRect frameCell {
            static_cast<int>((i == 0 ? startingCellPosition.x : (startingCellPosition.x + cellSize.x + cellSpacing.x) * i)),
            static_cast<int>(startingCellPosition.y + cellSpacing.y),
            static_cast<int>(cellSize.x),
            static_cast<int>(cellSize.y)
        };
        frameInfo.cell = frameCell;
        frames.push_back(frameInfo);
    }
}

void tails::AnimationInfo::stopAnimation()
{
    playing = false;
    currentFrame = 0;
}

tails::FrameInfo& tails::AnimationInfo::getCurrentFrame()
{
    return frames[currentFrame];
}

void tails::AnimationPlayer::update(float deltaTime)
{
    if (!m_sprite)
    {
        Debug::log("AnimationPlayer sprite is not set");
        return;
    }

    if (m_animations.empty())
    {
        Debug::log("AnimationPlayer contains no animations");
        return;
    }

    if (!m_animations.contains(m_currentAnimation))
    {
        Debug::log("AnimationPlayer does not contain the requested animation");
        return;
    }

    /**
     * We don't need setup or cleanup methods, because even if playAnimation is called mid-frame, it is either called
     * before this next line, or after it. And if it's before, then that's fine, we aren't doing anything specific
     * before aside from one check. If it's after, then that's fine, as we aren't using m_currentAnimation anymore,
     * we set a reference variable with whatever its value is, so all good there
     */
    AnimationInfo& animation = m_animations.at(m_currentAnimation);
    
    if (!animation.playing)
        return;

    m_sprite->setTextureRect(animation.getCurrentFrame().cell);

    const float overallPlayRate {m_playRate * (animation.playRate * animation.getCurrentFrame().length)};
    
    m_animTimer += deltaTime * overallPlayRate;

    // Return if we haven't reached the next frame yet
    if (m_animTimer < 1.f / overallPlayRate)
        return;
    
    animation.currentFrame++;

    if (animation.currentFrame >= animation.frames.size())
    {
        if (animation.loop)
        {
            animation.currentFrame = 0;
        }
        else
        {
            animation.playing = false;
        }
    }

    m_animTimer = 0.f;
}

void tails::AnimationPlayer::setTargetSprite(sf::Sprite* sprite)
{
    m_sprite = sprite;
}

sf::Sprite& tails::AnimationPlayer::getTargetSprite() const
{
    return *m_sprite;
}

tails::AnimationPlayer& tails::AnimationPlayer::addAnimation(const std::string& name, const sf::Vector2u cellSize,
    unsigned frames, const sf::Vector2u cellSpacing, const bool loop, const sf::Vector2u startingCellPosition,
    const float playRate)
{
    AnimationInfo animationInfo(this, cellSize, startingCellPosition, cellSpacing, loop, playRate);
    return addAnimation(name, animationInfo, frames);
}

tails::AnimationPlayer& tails::AnimationPlayer::addAnimation(const std::string& name, AnimationInfo& animation,
    unsigned frames)
{
    if (m_animations.contains(name))
    {
        Debug::log("Animation with that name already exists");
        return *this;
    }
    
    animation.setupFrames(frames);
    m_animations.emplace(name, animation);

    return *this;
}

void tails::AnimationPlayer::removeAnimation(const std::string& name)
{
    if (!m_animations.contains(name))
        return;

    m_animations.erase(name);
}

void tails::AnimationPlayer::playAnimation(const std::string& name, bool playFromStart)
{
    if (!m_animations.contains(name))
    {
        Debug::log("Failed to play animation - no animation with that name exists");
        return;
    }

    // Stop other animations that are playing
    for (auto& animation : std::ranges::views::values(m_animations))
    {
        if (animation.playing)
            animation.stopAnimation();
    }
    
    m_currentAnimation = name;
    m_animations.at(name).playing = true;

    if (playFromStart)
        m_animations.at(name).currentFrame = 0;
}

void tails::AnimationPlayer::pauseAnimation()
{
    pauseAnimation(m_currentAnimation);
}

void tails::AnimationPlayer::pauseAnimation(const std::string& name)
{
    if (!m_animations.contains(name))
        return;

    m_animations.at(name).playing = false;
}

void tails::AnimationPlayer::stopAllAnimations()
{
    m_currentAnimation = "";

    for (auto& animation : std::ranges::views::values(m_animations))
    {
        animation.stopAnimation();
    }
}

bool tails::AnimationPlayer::isAnimationPlaying()
{
    for (const auto& animation : std::ranges::views::values(m_animations))
    {
        if (animation.playing)
            return true;
    }

    return false;
}

const std::string& tails::AnimationPlayer::getCurrentAnimation()
{
    return m_currentAnimation;
}

const tails::AnimationInfo& tails::AnimationPlayer::getAnimationInfo(const std::string& name)
{
    if (!m_animations.contains(name))
        Debug::log("Cannot get animation info, animation with that name does not exist");
    
    return m_animations.at(name);
}

const tails::AnimationInfo& tails::AnimationPlayer::getCurrentAnimationInfo()
{
    return getAnimationInfo(getCurrentAnimation());
}

void tails::AnimationPlayer::setPlayRate(float playRate)
{
    m_playRate = playRate;
}

float tails::AnimationPlayer::getPlayRate() const
{
    return m_playRate;
}
