#include <Tails/Entities/SpriteEntity.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

#include <tuple>

namespace tails
{
    void SpriteEntity::setSpriteSheet(const sf::Texture& texture)
    {
        m_sprite.setTexture(texture);
    }

    Animation* SpriteEntity::createAnimation(const std::string& id)
    {
        std::vector<Frame> frames;
        return createAnimation(id, frames, 0, 1.f);
    }

    Animation* SpriteEntity::createAnimation(const std::string& id, std::vector<Frame> frames, int startingFrame, float speed)
    {
        m_anims.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(frames, startingFrame, speed));
        return &m_anims[id];
    }

    void SpriteEntity::addAnimation(const std::string& id, Animation animation)
    {
        m_anims[id] = animation;
    }

    void SpriteEntity::selectAnimation(const std::string& id)
    {
        if (!m_anims.contains(id)) return;

        m_currentAnim = &m_anims[id];
    }

    void SpriteEntity::play()
    {
        m_animPlaying = true;
    }

    void SpriteEntity::play(const std::string& id)
    {
        selectAnimation(id);
        m_animPlaying = true;
    }

    void SpriteEntity::pause()
    {
        m_animPlaying = false;
    }

    void SpriteEntity::tick(float deltaTime)
    {
        updateAnimation(deltaTime);
    }

    void SpriteEntity::updateAnimation(float deltaTime)
    {
        if (!m_animPlaying) return;
        if (!m_currentAnim) return;

        // play anim!
    }

    void SpriteEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(m_sprite, states);
    }
}
