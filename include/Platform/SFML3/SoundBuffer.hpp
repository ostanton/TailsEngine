#ifndef TAILS_SFML_SOUND_BUFFER_ASSET_HPP
#define TAILS_SFML_SOUND_BUFFER_ASSET_HPP

#include <Tails/Assets/Asset.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tails::sfml3
{
    class CSoundBuffer final : public IAsset
    {
        bool load(const std::filesystem::path& path) override
        {
            return m_buffer.loadFromFile(path);
        }

        sf::SoundBuffer m_buffer;
    };
}

#endif // TAILS_SFML_SOUND_BUFFER_ASSET_HPP
