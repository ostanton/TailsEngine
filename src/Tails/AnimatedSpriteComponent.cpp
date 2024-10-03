#include <Tails/AnimatedSpriteComponent.hpp>

#include <ranges>

namespace tails
{
    SFrame::SFrame(const sf::Rect<unsigned int>& frameRect, float framePlaybackSpeed)
        : rect(frameRect), playbackSpeed(framePlaybackSpeed)
    {
    }

    void SFrame::stop()
    {
        playbackTimer = 0.f;
    }

    SAnimation::SAnimation(
        const std::vector<SFrame>& inFrames,
        size_t initialFrameIndex,
        bool startPlaying,
        float inPlaybackSpeed,
        bool inLoop
    ) : frames(inFrames),
        currentFrameIndex(initialFrameIndex),
        playing(startPlaying),
        playbackSpeed(inPlaybackSpeed),
        loop(inLoop)
    {
    }

    void SAnimation::addFrame(const SFrame& frame)
    {
        frames.emplace_back(frame);
    }

    void SAnimation::addFrames(const std::vector<SFrame>& inFrames)
    {
        frames.insert(frames.end(), inFrames.begin(), inFrames.end());
    }

    void SAnimation::play()
    {
        playing = true;
    }

    void SAnimation::pause()
    {
        playing = false;
    }

    void SAnimation::stop()
    {
        pause();
        getCurrentFrame().stop();
        currentFrameIndex = 0;
    }

    CAnimatedSpriteComponent::CAnimatedSpriteComponent(AnimationMap animations)
        : m_animations(std::move(animations))
    {
    }

    void CAnimatedSpriteComponent::addAnimation(const std::string& name, const SAnimation& animation)
    {
        // TODO - weird access violation going on with key val when inserting into map
        m_animations.insert(AnimationMap::value_type(name, animation));
    }

    void CAnimatedSpriteComponent::play() const
    {
        if (!m_currentAnim) return;

        m_currentAnim->play();
    }

    void CAnimatedSpriteComponent::play(std::string_view name)
    {
        if (!m_animations.contains(name.data()))
        {
            CDebug::error("Failed to play animation \"", name, "\". It does not exist");
            return;
        }

        m_currentAnim = &m_animations[name.data()];
        m_currentAnim->play();
    }

    void CAnimatedSpriteComponent::pause() const
    {
        if (!m_currentAnim) return;

        m_currentAnim->pause();
    }

    void CAnimatedSpriteComponent::pause(std::string_view name)
    {
        if (!m_animations.contains(name.data())) return;

        m_animations[name.data()].pause();
    }

    void CAnimatedSpriteComponent::stop() const
    {
        if (!m_currentAnim) return;

        m_currentAnim->stop();
    }

    void CAnimatedSpriteComponent::stop(std::string_view name)
    {
        if (!m_animations.contains(name.data())) return;

        m_animations[name.data()].stop();
    }

    bool CAnimatedSpriteComponent::anyAnimationPlaying() const
    {
        if (m_currentAnim && m_currentAnim->playing) return true;

        for (auto& animation : std::views::values(m_animations))
        {
            if (animation.playing) return true;
        }

        return false;
    }

    void CAnimatedSpriteComponent::tick(float deltaTime)
    {
        if (!m_currentAnim || !m_currentAnim->playing) return;

        setTextureCoords(m_currentAnim->getCurrentFrame().rect);

        m_currentAnim->getCurrentFrame().playbackTimer += deltaTime;

        if (m_currentAnim->getCurrentFrame().playbackTimer <
            1.f * m_currentAnim->getCurrentFrame().playbackSpeed * m_currentAnim->playbackSpeed)
        {
            // return, as there is nothing to do while waiting for the next frame
            return;
        }

        if (m_currentAnim->currentFrameIndex + 1 >= m_currentAnim->frames.size())
        {
            if (m_currentAnim->loop)
                m_currentAnim->currentFrameIndex = 0;
            else
                stop();
        }
        else
        {
            m_currentAnim->currentFrameIndex++;
        }
    }
}
