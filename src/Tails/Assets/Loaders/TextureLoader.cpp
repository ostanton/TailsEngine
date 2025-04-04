#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Texture.hpp>

namespace tails
{
    std::shared_ptr<IAsset> CTextureLoader::load()
    {
        return std::make_shared<CTexture>();
    }
}
