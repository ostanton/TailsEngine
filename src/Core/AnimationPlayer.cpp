#include "TailsEngine/Core/AnimationPlayer.h"

#include <ranges>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TailsEngine/Debug/Debug.h"

void tails::AnimationInfo::setupFrames()
{
    // Create the frames of the animation from the sprite sheet and cell size
    const sf::Vector2u cellsInSheet {
        spriteSheet->getSize().x / cellSize.x,
        spriteSheet->getSize().y / cellSize.y
    };

    for (unsigned i {0}; i < cellsInSheet.x; i++)
    {
        FrameInfo frameInfo;
        // Set cell size. If i != 0 (>), we add our cell size and multiple by i to get the left position
        const sf::IntRect frameCell {
            static_cast<int>(i == 0 ? startingCellPosition.x : (startingCellPosition.x + cellSize.x) * i),
            static_cast<int>(startingCellPosition.y),
            static_cast<int>(cellSize.x),
            static_cast<int>(cellSize.y)
        };
        frameInfo.cell = frameCell;
        frames.push_back(frameInfo);
    }
}

void tails::AnimationPlayer::update(float deltaTime)
{
    if (!m_sprite)
    {
        Debug::log("AnimationPlayer sprite is not set");
        return;
    }
    
    if (!m_animations.contains(m_currentAnimation))
        return;

    AnimationInfo& animation = m_animations.at(m_currentAnimation);
    
    if (!animation.playing)
        return;

    m_sprite->setTextureRect(animation.frames[animation.currentFrame].cell);

    m_animTimer += deltaTime * m_playRate;

    // Return if we haven't reached the next frame yet
    if (m_animTimer < 1.f / m_playRate)
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

void tails::AnimationPlayer::addAnimation(const std::string& name, sf::Texture* spriteSheet,
    const sf::Vector2i cellSize, const sf::Vector2u startingCellPosition, const bool loop)
{
    AnimationInfo animationInfo(spriteSheet, cellSize, startingCellPosition, loop);
    addAnimation(name, animationInfo);
}

void tails::AnimationPlayer::addAnimation(const std::string& name, AnimationInfo& animation)
{
    if (m_animations.contains(name))
        return;
    
    animation.setupFrames();
    m_animations.emplace(name, animation);
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
        return;

    m_currentAnimation = name;
    m_animations.at(name).playing = true;

    if (m_sprite->getTexture() != m_animations.at(name).spriteSheet)
        m_sprite->setTexture(*m_animations.at(name).spriteSheet);

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
        animation.playing = false;
        animation.currentFrame = 0;
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
