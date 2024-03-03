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
    bool loop {true};
    bool playing {false};
    size_t currentFrame {0};

    AnimationInfo(
        sf::Texture* inSpriteSheet,
        const sf::Vector2i inCellSize,
        const sf::Vector2u inStartingCellPosition,
        const bool inLoop)
        :
    spriteSheet(inSpriteSheet),
    cellSize(inCellSize),
    startingCellPosition(inStartingCellPosition),
    loop(inLoop) {}

    void setupFrames();
    void stopAnimation();
};

class AnimationPlayer
{
public:
    /**
     * \brief Called every frame, updates the state of the current animation
     * \param deltaTime Time since last frame
     */
    void update(float deltaTime);

    /**
     * \brief Sets the target sprite to play the animations on
     * \param sprite Sprite to apply the animation to
     */
    void setTargetSprite(sf::Sprite* sprite);
    
    /**
     * \brief Adds an animation with the specified settings to the AnimationPlayer's m_animations vector ready to be
     * played
     * \param name Name of the animation
     * \param spriteSheet Texture used for the animation
     * \param cellSize Size of each cell in the sprite sheet
     * \param startingCellPosition Where the animation starts in the sprite sheet
     * \param loop Should this animation play from start when it reaches the end
     */
    void addAnimation(const std::string& name, sf::Texture* spriteSheet, const sf::Vector2i cellSize,
        const bool loop = true, const sf::Vector2u startingCellPosition = {0, 0});
    
    /**
     * \brief Adds an animation with the specified settings to the AnimationPlayer's m_animations vector ready to be
     * played
     * \param name Name of the animation
     * \param animation Settings for the animation
     */
    void addAnimation(const std::string& name, AnimationInfo& animation);
    
    /**
     * \brief Removes an animation from the AnimationPlayer's m_animations vector. This animation can no longer be
     * played
     * \param name Animation to remove
     */
    void removeAnimation(const std::string& name);

    /**
     * \brief Plays an animation that this AnimationPlay has
     * \param name Animation to play
     * \param playFromStart Whether to play the animation from the start
     */
    void playAnimation(const std::string& name, bool playFromStart = true);
    
    /**
     * \brief Pauses the current animation
     */
    void pauseAnimation();
    
    /**
     * \brief Pauses the specified animation
     * \param name Animation to pause
     */
    void pauseAnimation(const std::string& name);
    
    /**
     * \brief Stops all animations playing (resetting them)
     */
    void stopAllAnimations();

    /**
     * \brief Checks if any animation is currently playing
     * \return True if there is an animation playing
     */
    bool isAnimationPlaying();
    
    /**
     * \brief Get the current animation being played
     * \return Name of animation
     */
    const std::string& getCurrentAnimation();

    /**
     * \brief Get the information of a specific animation
     * \param name Animation name
     * \return Animation information
     */
    const AnimationInfo& getAnimationInfo(const std::string& name);

    /**
     * \brief Get the information of the current animation
     * \return Animation information
     */
    const AnimationInfo& getCurrentAnimationInfo();

    /**
     * \brief Set the play rate of this AnimationPlayer (speed multiplier, e.g. 2 is twice as fast)
     * \param playRate Rate of the animation
     */
    void setPlayRate(float playRate);

    /**
     * \brief Get the play rate of this AnimationPlayer
     * \return The play rate
     */
    [[nodiscard]] float getPlayRate() const;

private:
    /**
     * \brief Map of all the animations contained in this AnimationPlayer. Each animation has a name and information,
     * containing its frames, current frame index, etc.
     */
    std::unordered_map<std::string, AnimationInfo> m_animations;
    
    /**
     * \brief Sprite to animate. This comes from the Entity that has the sprite component itself, so its memory
     * is managed there
     */
    sf::Sprite* m_sprite {nullptr};
    std::string m_currentAnimation;
    float m_playRate {1.f}; // TODO could have different animations have different play rates?
    float m_animTimer {0.f};
};

}
