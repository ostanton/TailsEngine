#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Assets/AssetRegistry.hpp>

namespace tails
{
    enum class EMyAssetTypes
    {
        GIF,
        Music
    };

    std::shared_ptr<IAsset> CAssetManager::getAsset(const EAssetType type)
    {
        return getAsset(static_cast<u8>(type));
    }

    std::shared_ptr<IAsset> CAssetManager::getAsset(const u8 assetID)
    {
        const auto asset = CAssetRegistry::get().loadAssetFromFileImpl(assetID, "");
        m_loadedAssets.emplace_back(asset);
        return asset;
    }
}
