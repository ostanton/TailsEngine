#ifndef TAILS_SOUND_BUS_HPP
#define TAILS_SOUND_BUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Bus.hpp>

#include <SFML/Audio/Sound.hpp>

namespace tails
{
    class TAILS_API CSoundBus : public IBus
    {
    public:
        CSoundBus(const sf::SoundBuffer& buffer);
        
    protected:
        void play() override;
        void stop() override;
        void pause() override;
        
    private:
        // TODO - can just have this be unique_ptr instead?
        // not amazing but beats making my own sound
        sf::Sound m_sound;
    };
}

#endif // TAILS_SOUND_BUS_HPP
