#ifndef TAILS_MUSICBUS_HPP
#define TAILS_MUSICBUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Audio/Bus.hpp>

#include <SFML/Audio/Music.hpp>

namespace tails
{
    class TAILS_API MusicBus : public Bus
    {
    public:
        void setAsset(const AssetInfo &asset) override;

        void play() override;
        void pause() override;
        void stop() override;

        void setVolume(float volume) override;

    private:
        sf::Music m_music;
    };
} // tails

#endif //TAILS_MUSICBUS_HPP
