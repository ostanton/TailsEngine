#ifndef TAILS_TEXTURE_LOADER_HPP
#define TAILS_TEXTURE_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    class CTexture;
    
    class TAILS_API CTextureLoader : public IAssetLoader
    {
    public:
        using AssetType = CTexture;
        
        std::shared_ptr<IAsset> load(const CString& path) override;
    };
}

#endif // TAILS_TEXTURE_LOADER_HPP
