#ifndef TAILS_SOUNDASSET_HPP
#define TAILS_SOUNDASSET_HPP

#include <Tails/Config.hpp>
#include <Tails/AssetData.hpp>

#include <SFML/Audio/SoundBuffer.hpp>

#include <string>

namespace tails
{
    class TAILS_API CSoundAsset final : public IAssetData, public sf::SoundBuffer
    {
        bool load(const std::string& path) override;
        std::string getType() override;
    };
}

#endif // TAILS_SOUNDASSET_HPP
