#include "TailsEngine/Managers/MusicManager.h"

#include "TailsEngine/Debug/Debug.h"

bool tails::MusicManager::loadMusic(const std::string& path)
{
    if (!m_music.openFromFile(path))
    {
        Debug::log("MusicManager::loadMusic - Failed to load music from path");
        return false;
    }

    return true;
}

void tails::MusicManager::loadAndPlayMusic(const std::string& path)
{
    loadMusic(path);
    m_music.play();
}

sf::Music& tails::MusicManager::getMusic()
{
    return m_music;
}

void tails::MusicManager::play()
{
    m_music.play();
}

void tails::MusicManager::pause()
{
    m_music.pause();
}

void tails::MusicManager::stop()
{
    m_music.stop();
}
