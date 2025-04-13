#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Texture.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>

#include <fstream>

namespace tails
{
    std::shared_ptr<IAsset> CTextureLoader::load(const char* path)
    {
        std::ifstream file {path};
        // TODO - load file with stb_image or something and convert to tails' CTexture
        // load image via stb_image, copy relevant data into new CTexture, delete stb texture, return CTexture
        const auto result = assets::allocateAsset<CTexture>(SVector2u {8, 8}, nullptr);
        return result;
    }
}
