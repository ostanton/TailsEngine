#include <Tails/Audio/SoundBus.hpp>
#include <Tails/Debug.hpp>
#include <Tails/Resources/SoundBuffer.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tails
{
    CSoundBus::CSoundBus()
        : m_sound(m_emptyBuffer)
    {}

    CSoundBus::CSoundBus(const std::shared_ptr<CSoundBuffer>& resource) noexcept
        : m_sound(*resource->getUnderlying<sf::SoundBuffer>()), m_buffer(resource)
    {}

    CSoundBus::CSoundBus(CSoundBus&&) noexcept = default;
    CSoundBus& CSoundBus::operator=(CSoundBus&&) noexcept = default;
    CSoundBus::~CSoundBus() = default;

    void CSoundBus::setResourceImpl(const std::shared_ptr<CSoundBuffer>& resource)
    {
        m_buffer = resource;
        if (m_buffer)
            if (auto const buffer = m_buffer->getUnderlying<sf::SoundBuffer>())
                m_sound.setBuffer(*buffer);
    }

    void CSoundBus::play()
    {
        m_sound.play();
    }

    void CSoundBus::stop()
    {
        m_sound.stop();
    }

    void CSoundBus::pause()
    {
        m_sound.pause();
    }
}
