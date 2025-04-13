#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Asset.hpp>

namespace tails
{
    std::shared_ptr<IAsset> SAssetPath::load() const
    {
        return impl::CAssetRegistry::get().loadAssetFromFile(assetType, path);
    }
}
