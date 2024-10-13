#include <Tails/SoundBus.hpp>

namespace tails
{
    CSoundBus::CSoundBus(const sf::SoundBuffer& buffer)
        : m_sound(buffer)
    {
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
