#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Filesystem.hpp>

namespace tails
{
    SAssetPath::SAssetPath(const u8 inAssetType, CString inPath)
        : assetType(inAssetType), path(std::move(inPath))
    {
        path.insert(0, fs::getBasePath());
    }

    std::shared_ptr<IAsset> SAssetPath::load() const
    {
        return assets::loadAsset(assetType, path);
    }
}
