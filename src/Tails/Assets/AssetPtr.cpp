#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Application.hpp>
#include <Tails/Assets/Asset.hpp>

namespace tails
{
    SAssetPtr::SAssetPtr(const IAsset& asset)
        : assetType(static_cast<u8>(asset.getAssetType()) + asset.getCustomAssetType())
    {
    }

    std::shared_ptr<IAsset> SAssetPtr::load(const char* filename, CAssetManager* assetManager) const
    {
        if (assetManager)
            return assetManager->getAsset(assetType);

        return IApplication::get().getAssetManager().getAsset(assetType);
    }
}
