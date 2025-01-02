#ifndef TAILS_SOUND_BUFFER_RESOURCE_HPP
#define TAILS_SOUND_BUFFER_RESOURCE_HPP

#include <Tails/Config.hpp>
#include <Tails/Resources/Resource.hpp>

#include <SFML/Audio/SoundBuffer.hpp>

namespace tails
{
    class TAILS_API CSoundBuffer final : public IResource
    {
    private:
        bool load(const std::filesystem::path& path) override;
        const void* getUnderlyingImpl() const override;
        
        sf::SoundBuffer m_buffer;
    };
}

#endif // TAILS_SOUND_BUFFER_RESOURCE_HPP
