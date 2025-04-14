#ifndef TAILS_TEXTURE_LOADER_HPP
#define TAILS_TEXTURE_LOADER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Loaders/AssetLoader.hpp>

namespace tails
{
    class TAILS_API CTextureLoader : public IAssetLoader
    {
    public:
        std::shared_ptr<IAsset> load(const char* path) override;
    };
}

#endif // TAILS_TEXTURE_LOADER_HPP
