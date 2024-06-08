#include <Tails/Subsystems/AssetSubsystem.hpp>

namespace tails
{
    uint32_t AssetSubsystem::createAsset(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string& path)
    {
        m_assets[m_currentID] = AssetInfo(resourceType, assetType, path);
        m_currentID++;
        return m_currentID - 1;
    }

    bool AssetSubsystem::isValidID(uint32_t id)
    {
        return m_assets.contains(id);
    }

    AssetInfo& AssetSubsystem::getAsset(uint32_t id)
    {
        return m_assets[id];
    }

    void AssetSubsystem::destroyAsset(uint32_t id)
    {
        if (!m_assets.contains(id)) return;

        m_assets.erase(id);
    }
}
