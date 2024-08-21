#ifndef TAILS_FONTASSET_HPP
#define TAILS_FONTASSET_HPP

#include <Tails/Config.hpp>
#include <Tails/AssetData.hpp>

#include <SFML/Graphics/Font.hpp>

namespace tails
{
    class TAILS_API CFontAsset : public IAssetData, public sf::Font
    {
        bool load(const std::string& path) override;
        std::string getType() const override;
    };
}

#endif // TAILS_FONTASSET_HPP
