#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Assets/AssetRegistry.hpp>

namespace tails
{
    void CAssetManager::addAsset(const std::shared_ptr<IAsset>& asset)
    {
        m_loadedAssets.emplace_back(asset);
    }
}
