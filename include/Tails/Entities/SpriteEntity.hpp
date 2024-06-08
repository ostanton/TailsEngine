#ifndef TAILS_SPRITEENTITY_HPP
#define TAILS_SPRITEENTITY_HPP

#include <Tails/Entities/Entity.hpp>

#include <SFML/Graphics/Sprite.hpp>

#include <unordered_map>
#include <string>
#include <vector>

namespace tails
{
    struct Frame
    {
        sf::FloatRect rect; // rect of the frame on the sprite sheet
        float speed {1.f}; // multiplier, e.g. 0.5x = twice as long
    };

    struct Animation
    {
        Animation() = default;
        Animation(std::vector<Frame> inFrames, int initialFrame, float inSpeed)
            : frames(inFrames), currentFrame(initialFrame), speed(inSpeed) {}

        std::vector<Frame> frames; // the frames to play through
        int currentFrame; // current frame index
        float speed {1.f}; // multiplier

        const Frame& getCurrentFrame() {return frames[currentFrame];}
    };

    // wrapper for SFML sprite that can be animated
    class SpriteEntity : public Entity
    {
    public:
        void setSpriteSheet(const sf::Texture& texture);

        // animations
        Animation* createAnimation(const std::string& id); // constructs a default animation object in-place
        Animation* createAnimation(const std::string& id, std::vector<Frame> frames, int startingFrame, float speed); // constructs a new animation object in-place
        void addAnimation(const std::string& id, Animation animation); // adds an existing animation object
        void selectAnimation(const std::string& id); // select an animation, does not autoplay
        void play(); // play the current animation
        void play(const std::string& id); // selects and plays an animation
        void pause(); // pause the current animation
        const Animation& getCurrentAnimation() {return *m_currentAnim;} // returns the current animation

    protected:
        void tick(float deltaTime) override;
        void updateAnimation(float deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        bool m_animPlaying; // is the selected animation playing?
        std::unordered_map<std::string, Animation> m_anims; // list of available animations mapped to an ID
        Animation* m_currentAnim; // pointer to currently selected animation
        sf::Sprite m_sprite; // sprite to draw and apply animation to
    };
}

#endif // TAILS_SPRITEENTITY_HPP
