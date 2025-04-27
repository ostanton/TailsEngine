#ifndef TAILS_TEXTURE_LOADER_HPP
#define TAILS_TEXTURE_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>
#include <Tails/Assets/Texture.hpp>

namespace tails
{
    class TAILS_API CTextureLoader : public IAssetLoader
    {
    public:
        using AssetType = CTexture;
        
        std::shared_ptr<IAsset> load(const CString& path) override;
    };
}

#endif // TAILS_TEXTURE_LOADER_HPP
