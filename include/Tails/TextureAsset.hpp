#ifndef TAILS_TEXTUREASSET_HPP
#define TAILS_TEXTUREASSET_HPP

#include <Tails/Config.hpp>
#include <Tails/AssetData.hpp>

#include <SFML/Graphics/Texture.hpp>

#include <string>

namespace tails
{
    class TAILS_API CTextureAsset final : public IAssetData, public sf::Texture
    {
        bool load(const std::string& path) override;
        std::string getType() const override;
    };
}

#endif // TAILS_TEXTUREASSET_HPP
