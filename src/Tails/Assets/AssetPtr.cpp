#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>

namespace tails
{
    std::shared_ptr<IAsset> SAssetPath::load() const
    {
        return assets::loadAsset(assetType, path);
    }
}
