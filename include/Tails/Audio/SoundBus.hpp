#ifndef TAILS_SOUND_BUS_HPP
#define TAILS_SOUND_BUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Audio/Bus.hpp>

#include <memory>

namespace sf
{
    class Sound;
    class SoundBuffer;
}

namespace tails
{
    class TAILS_API CSoundBus final : public IBus
    {
    public:
        CSoundBus();
        explicit CSoundBus(const sf::SoundBuffer* resource) noexcept;
        CSoundBus(const CSoundBus&) = delete;
        CSoundBus(CSoundBus&&) noexcept;
        CSoundBus& operator=(const CSoundBus&) = delete;
        CSoundBus& operator=(CSoundBus&&) noexcept;
        ~CSoundBus() override;
        
    protected:
        void setResourceImpl(void* resource) override;
        
        void play() override;
        void stop() override;
        void pause() override;
        
    private:
        bool createSound(const sf::SoundBuffer& resource) noexcept;

        // dynamic allocation because sf::Sound requires an sf::SoundBuffer,
        // but I want to be able to have a sound without a buffer, and I do not want
        // to make my own sound class
        std::unique_ptr<sf::Sound> m_sound;
    };
}

#endif // TAILS_SOUND_BUS_HPP
