#include <Tails/Managers/Asset.hpp>

namespace tails
{
    uint32_t AssetManager::createAsset(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string& path)
    {
        m_assets[m_currentID] = AssetInfo(resourceType, assetType, path);
        m_currentID++;
        return m_currentID - 1;
    }

    bool AssetManager::isValidID(uint32_t id)
    {
        return m_assets.contains(id);
    }

    AssetInfo& AssetManager::getAsset(uint32_t id)
    {
        return m_assets[id];
    }

    void AssetManager::destroyAsset(uint32_t id)
    {
        if (!m_assets.contains(id)) return;

        m_assets.erase(id);
    }
}
