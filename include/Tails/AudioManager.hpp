#ifndef TAILS_AUDIOMANAGER_HPP
#define TAILS_AUDIOMANAGER_HPP

#include <Tails/Config.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>

#include <string>
#include <memory>

namespace tails
{
    class CSoundAsset;

    class TAILS_API CAudioManager final
    {
    public:
        static void playSound(const std::string& assetID);
        static void playSound(std::shared_ptr<CSoundAsset> asset);

        static void playMusic(const std::string& path);

    private:
        static CAudioManager& get();

        // TODO - sort out whatever is happening here
        // how many channels do we support, what are the limitations?
        // what about .mod, .it, etc. files? Tracker stuff, and/or midi stuff??
        sf::Sound m_sound;
        sf::Music m_music;
    };
}

#endif // TAILS_AUDIOMANAGER_HPP
