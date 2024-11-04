#include <Tails/Audio/SoundBus.hpp>
#include <Tails/Debug.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/System/Exception.hpp>

namespace tails
{
    CSoundBus::CSoundBus() = default;

    CSoundBus::CSoundBus(const sf::SoundBuffer* resource) noexcept
    {
        if (resource)
            createSound(*resource);
    }

    CSoundBus::CSoundBus(CSoundBus&&) noexcept = default;
    CSoundBus& CSoundBus::operator=(CSoundBus&&) noexcept = default;
    CSoundBus::~CSoundBus() = default;

    void CSoundBus::setResourceImpl(void* resource)
    {
        if (!resource)
        {
            CDebug::error("Sound resource to play is null!");
            return;
        }

        createSound(*static_cast<sf::SoundBuffer*>(resource));
    }

    void CSoundBus::play()
    {
        if (m_sound)
            m_sound->play();
    }

    void CSoundBus::stop()
    {
        if (m_sound)
            m_sound->stop();
    }

    void CSoundBus::pause()
    {
        if (m_sound)
            m_sound->pause();
    }

    bool CSoundBus::createSound(const sf::SoundBuffer& resource) noexcept
    {
        try {m_sound = std::make_unique<sf::Sound>(resource);}
        catch (const sf::Exception& e)
        {
            CDebug::exception("Sound bus failed to set resource: ", e.what());
            return false;
        }
        catch (...)
        {
            CDebug::exception("Unknown exception while setting sound bus resource");
            return false;
        }

        return true;
    }
}
