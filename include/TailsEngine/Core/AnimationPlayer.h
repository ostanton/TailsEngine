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
/**
 * \brief Provides information for a single frame. Currently only the cell information, but could be whatever.
 * Could in the future have individual frame lengths
 */
struct FrameInfo
{
    sf::IntRect cell;
    float length {1.f};
};

class AnimationPlayer;

/**
 * \brief Provides information for a single animation, like its frames, cell size, if it loops, etc.
 * Could in the future have individual animation play rates
 */
struct AnimationInfo
{
    AnimationPlayer* owningPlayer;
    std::vector<FrameInfo> frames;
    sf::Vector2u cellSize;
    sf::Vector2u startingCellPosition;
    bool loop {true};
    bool playing {false};
    size_t currentFrame {0};
    float playRate {1.f};

    AnimationInfo(
        AnimationPlayer* owner,
        const sf::Vector2i inCellSize,
        const sf::Vector2u inStartingCellPosition,
        const bool inLoop,
        const float inPlayRate)
        :
    owningPlayer(owner),
    cellSize(inCellSize),
    startingCellPosition(inStartingCellPosition),
    loop(inLoop),
    playRate(inPlayRate) {}

    void setupFrames(unsigned frameAmount);
    void stopAnimation();
    FrameInfo& getCurrentFrame();
};

/**
 * \brief A class that plays through sprite sheets and draws them to an sf::Sprite.
 *
 * It only works with rows. You can specify a position in the sprite sheet to start (should be at the left edge),
 * and it iterates through each cell, drawing it to the sprite every second * playRate.
 *
 * It assumes the target sprite always has a texture set
 */
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
     * \brief Gets the target sprite that the animation is being applied to
     * \return Sprite the animation is applied to
     */
    sf::Sprite& getTargetSprite() const;
    
    /**
     * \brief Adds an animation with the specified settings to the AnimationPlayer's m_animations vector ready to be
     * played
     * \param name Name of the animation
     * \param cellSize Size of each cell in the sprite sheet
     * \param frames How many frames this animation has
     * \param startingCellPosition Where the animation starts in the sprite sheet
     * \param loop Should this animation play from start when it reaches the end
     * \param playRate The speed of this animation
     */
    AnimationPlayer& addAnimation(const std::string& name, const sf::Vector2i cellSize, unsigned frames,
        const bool loop = true, const sf::Vector2u startingCellPosition = {0, 0}, const float playRate = 1.f);
    
    /**
     * \brief Adds an animation with the specified settings to the AnimationPlayer's m_animations vector ready to be
     * played
     * \param name Name of the animation
     * \param animation Settings for the animation
     * \param frames How many frames this animation has
     */
    AnimationPlayer& addAnimation(const std::string& name, AnimationInfo& animation, unsigned frames);
    
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

    /**
     * \brief The animation we are currently playing (can be ""/null)
     */
    std::string m_currentAnimation;

    /**
     * \brief The play rate (speed multiplier) for all animations
     *
     * TODO could have different animations have different play rates?
     */
    float m_playRate {1.f};

    /**
     * \brief The current time in the current we are. Used to check when we should move to the next frame
     */
    float m_animTimer {0.f};
};

}
