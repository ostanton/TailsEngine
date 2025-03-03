#ifndef TAILS_SFML_TEXTURE_ASSET_HPP
#define TAILS_SFML_TEXTURE_ASSET_HPP

#include <Tails/Assets/Asset.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tails::sfml3
{
    class CTexture final : public IAsset
    {
        bool load(const std::filesystem::path& path) override
        {
            return m_texture.loadFromFile(path);
        }

        sf::Texture m_texture;
    };
}

#endif // TAILS_SFML_TEXTURE_ASSET_HPP
