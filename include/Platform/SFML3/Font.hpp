#ifndef TAILS_SFML_FONT_ASSET_HPP
#define TAILS_SFML_FONT_ASSET_HPP

#include <Tails/Assets/Asset.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tails::sfml3
{
    class CFont final : public IAsset
    {
        bool load(const std::filesystem::path& path) override
        {
            return m_font.openFromFile(path);
        }

        sf::Font m_font;
    };
}

#endif // TAILS_SFML_FONT_ASSET_HPP
