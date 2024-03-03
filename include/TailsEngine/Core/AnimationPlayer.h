#pragma once
#include <string>
#include <unordered_map>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace sf
{
class Sprite;
class Texture;
}

namespace tails
{
struct FrameInfo
{
    sf::IntRect cell;
};

struct AnimationInfo
{
    std::vector<FrameInfo> frames;
    /**
     * \brief The sprite sheet where the animation is located. This comes from an asset cache, so its memory
     * is managed there
     */
    sf::Texture* spriteSheet;
    sf::Vector2u cellSize;
    sf::Vector2u startingCellPosition;
    bool playing {false};
    size_t currentFrame {0};
    bool loop {true};

    AnimationInfo(
        sf::Texture* inSpriteSheet,
        const sf::Vector2i inCellSize,
        const sf::Vector2u inStartingCellPosition)
        :
    spriteSheet(inSpriteSheet),
    cellSize(inCellSize),
    startingCellPosition(inStartingCellPosition) {}

    void setupFrames();
};

class AnimationPlayer
{
public:
    void update(float deltaTime);

    void setTargetSprite(sf::Sprite* sprite);
    void addAnimation(const std::string& name, sf::Texture* spriteSheet, const sf::Vector2i cellSize,
        const sf::Vector2u startingCellPosition = {0, 0});
    void addAnimation(const std::string& name, AnimationInfo& animation);
    void removeAnimation(const std::string& name);

    void playAnimation(const std::string& name, bool playFromStart = false);
    void pauseAnimation();
    void pauseAnimation(const std::string& name);
    void stopAllAnimations();
    
    bool isAnimationPlaying();
    std::string& getCurrentAnimation();

private:
    std::unordered_map<std::string, AnimationInfo> m_animations;
    /**
     * \brief Sprite to animate. This comes from the Entity that has the sprite component itself, so its memory
     * is managed there
     */
    sf::Sprite* m_sprite {nullptr};
    std::string m_currentAnimation;
    float m_playRate {1.f};
    float m_animTimer {0.f};
};

}
