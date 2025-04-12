#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Assets/AssetDeleter.hpp>

#include <iostream>

namespace tails
{
    void CAssetManager::addAsset(const std::shared_ptr<IAsset>& asset)
    {
        std::cout << "Adding asset!\n";
        // TODO - when move to map, give deleter the asset handle so it knows which asset to erase
        std::get_deleter<SAssetDeleter>(asset)->assetManagers.push_back(this);
        m_loadedAssets.emplace_back(asset);
    }
}
