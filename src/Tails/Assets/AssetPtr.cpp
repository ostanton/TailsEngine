#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>

#include <SDL3/SDL_filesystem.h>

namespace tails
{
    SAssetPath::SAssetPath(const u8 inAssetType, CString inPath)
        : assetType(inAssetType), path(std::move(inPath))
    {
        path.insert(0, SDL_GetBasePath());
    }

    std::shared_ptr<IAsset> SAssetPath::load() const
    {
        return assets::loadAsset(assetType, path);
    }
}
