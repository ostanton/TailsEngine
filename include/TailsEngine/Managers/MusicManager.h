#pragma once
#include <SFML/Audio/Music.hpp>

namespace tails
{
/**
 * \brief A class that manages current music being played. Mostly just a wrapper for sf::Music. Intended to be
 * used on a Level basis. One MusicManager for each level. More can be used however, but it's up to you to manage them
 */
class MusicManager
{
public:
    bool loadMusic(const std::string& path);
    void loadAndPlayMusic(const std::string& path);
    sf::Music& getMusic();

    void play();
    void pause();
    void stop();

private:
    sf::Music m_music;
};

}
