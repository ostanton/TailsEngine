#ifndef TAILS_SOUNDBUS_HPP
#define TAILS_SOUNDBUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Audio/Bus.hpp>

#include <SFML/Audio/Sound.hpp>

namespace tails
{
    /**
     * A bus that holds an SFML sf::Sound. Intended to only be for short, one-shot sounds, but can loop.
     */
    class TAILS_API SoundBus : public Bus
    {
    public:
        void setAsset(const AssetInfo& asset) override;

        void play() override;
        void pause() override;
        void stop() override;

        void setVolume(float volume) override;

        void setLooping(bool looping) override;
        [[nodiscard]] bool getLooping() const override;

        void setPitch(float pitch) override;
        [[nodiscard]] float getPitch() const override;

    private:
        sf::Sound m_sound;
    };
} // tails

#endif //TAILS_SOUNDBUS_HPP
