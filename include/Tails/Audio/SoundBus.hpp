#ifndef TAILS_SOUND_BUS_HPP
#define TAILS_SOUND_BUS_HPP

#include <Tails/Config.hpp>
#include <Tails/Audio/Bus.hpp>

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tails
{
    class TAILS_API CSoundBus final : public IBus
    {
    public:
        CSoundBus();
        explicit CSoundBus(const std::shared_ptr<CSoundBuffer>& resource) noexcept;
        CSoundBus(const CSoundBus&) = delete;
        CSoundBus(CSoundBus&&) noexcept;
        CSoundBus& operator=(const CSoundBus&) = delete;
        CSoundBus& operator=(CSoundBus&&) noexcept;
        ~CSoundBus() override;
        
    protected:
        void setResourceImpl(const std::shared_ptr<CSoundBuffer>& resource) override;
        
        void play() override;
        void stop() override;
        void pause() override;
        
    private:
        sf::Sound m_sound;
        sf::SoundBuffer m_emptyBuffer;
        std::shared_ptr<CSoundBuffer> m_buffer;
    };
}

#endif // TAILS_SOUND_BUS_HPP
