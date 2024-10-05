#ifndef TAILS_ANIMATED_SPRITE_COMPONENT_HPP
#define TAILS_ANIMATED_SPRITE_COMPONENT_HPP

#include <Tails/Config.hpp>
#include <Tails/SpriteComponent.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <unordered_map>
#include <string>

namespace tails
{
    struct TAILS_API SFrame final
    {
        SFrame() = default;
        SFrame(const sf::Rect<unsigned int>& frameRect, float framePlaybackSpeed = 1.f);
        SFrame(const SFrame&) = default;
        SFrame(SFrame&&) = default;
        SFrame& operator=(const SFrame&) = default;
        SFrame& operator=(SFrame&&) = default;
        ~SFrame() = default;
        
        /**
         * Rectangle representing this frame's bounds in the texture
         */
        sf::Rect<unsigned int> rect;

        float playbackSpeed {1.f};
        float playbackTimer {0.f};

        /**
         * Stop this frame from playing
         */
        void stop();
    };
    
    struct TAILS_API SAnimation final
    {
        SAnimation() = default;
        SAnimation(
            const std::vector<SFrame>& inFrames,
            float inPlaybackSpeed = 1.f,
            bool inLoop = true,
            size_t initialFrameIndex = 0,
            bool startPlaying = false
        );
        SAnimation(const SAnimation&) = default;
        SAnimation(SAnimation&&) = default;
        SAnimation& operator=(const SAnimation&) = default;
        SAnimation& operator=(SAnimation&&) = default;
        ~SAnimation() = default;
        
        std::vector<SFrame> frames;
        float playbackSpeed {1.f};
        bool loop {true};
        size_t currentFrameIndex {0};
        bool playing {false};

        void addFrame(const SFrame& frame);
        void addFrames(const std::vector<SFrame>& inFrames);

        void play();
        void pause();
        void stop();

        [[nodiscard]] SFrame& getCurrentFrame() {return frames[currentFrameIndex];}
        [[nodiscard]] const SFrame& getCurrentFrame() const {return frames[currentFrameIndex];}
    };
    
    /**
     * Treats the associated texture as a sprite-sheet, and allows frames to be created using rectangles
     * on that sprite-sheet, forming animations that can be played, paused, and stopped.
     */
    class TAILS_API CAnimatedSpriteComponent final : public CSpriteComponent
    {
    public:
        using AnimationMap = std::unordered_map<std::string, SAnimation>;
        
        CAnimatedSpriteComponent() = default;
        CAnimatedSpriteComponent(AnimationMap animations);

        /**
         * 
         * @param name Animation name
         * @param animation Animation to add
         */
        void addAnimation(const std::string& name, const SAnimation& animation);

        /**
         * Plays the current animation
         */
        void play() const;
        
        /**
         * Plays the specified animation
         * @param name Animation name
         */
        void play(std::string_view name);
        
        /**
         * Pauses the current animation
         */
        void pause() const;

        /**
         * Pauses the specified animation
         * @param name Animation name
         */
        void pause(std::string_view name);

        /**
         * Stops the current animation
         */
        void stop() const;

        /**
         * Stops the specified animation
         * @param name Animation name
         */
        void stop(std::string_view name);

        /**
         * Check if there is any animation playing
         * @return True if there is an animation playing
         */
        [[nodiscard]] bool anyAnimationPlaying() const;

    private:
        void tick(float deltaTime) override;

        AnimationMap m_animations;
        SAnimation* m_currentAnim {nullptr};
    };
}
TAILS_REGISTER_CLASS(CAnimatedSpriteComponent)

#endif // TAILS_ANIMATED_SPRITE_COMPONENT_HPP
