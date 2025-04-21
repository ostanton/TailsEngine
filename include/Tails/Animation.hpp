#ifndef TAILS_ANIMATION_HPP
#define TAILS_ANIMATION_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/Transform2D.hpp>

#include <vector>
#include <memory>
#include <string_view>
#include <unordered_map>

namespace tails
{
    class CTexture;
    class CString;
    class CRenderer;
    
    struct TAILS_API SFrame final
    {
        /** The rectangle in the sprite sheet that this frame shows */
        SIntRect bounds;
        
        /** Multiplier for how long this frame lasts */
        float playRate;
    };

    struct TAILS_API SAnimation final
    {
        std::vector<SFrame> frames;
        usize frameRate;
        usize currentFrame;
        bool loop;
    };

    struct TAILS_API SAnimationPlayer final
    {
        SAnimationPlayer() = default;
        explicit SAnimationPlayer(const CString& spriteSheetPath);
        explicit SAnimationPlayer(std::shared_ptr<CTexture> inSpriteSheet);
        SAnimationPlayer(const SAnimationPlayer&) = default;
        SAnimationPlayer(SAnimationPlayer&&) noexcept = default;
        SAnimationPlayer& operator=(const SAnimationPlayer&) = default;
        SAnimationPlayer& operator=(SAnimationPlayer&&) noexcept = default;
        ~SAnimationPlayer() = default;

        void addAnimation(std::string_view name, SAnimation animation);
        [[nodiscard]] SAnimation* getAnimation(std::string_view name) noexcept;
        [[nodiscard]] const SAnimation* getAnimation(std::string_view name) const noexcept;
        [[nodiscard]] bool containsAnimation(std::string_view name) const noexcept;
        void playAnimation(std::string_view name) noexcept;
        [[nodiscard]] SAnimation* getPlayingAnimation() noexcept;
        [[nodiscard]] const SAnimation* getPlayingAnimation() const noexcept;
        bool removeAnimation(std::string_view name) noexcept;

        void tick(float deltaSeconds);
        void render(
            const CRenderer& renderer,
            const STransform2D& transform,
            SColour colour
        ) const;

        std::shared_ptr<CTexture> spriteSheet;
        std::string_view playingAnimation;
        std::unordered_map<std::string_view, SAnimation> animations;
        float currentTime {0.f};
    };
}

#endif // TAILS_ANIMATION_HPP
