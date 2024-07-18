#include <Tails/Subsystems/AssetSubsystem.hpp>

namespace tails
{
    uint32_t AssetSubsystem::createAsset(const std::string& jsonPath)
    {
        m_assets.try_emplace(m_currentID, AssetInfo(jsonPath));
        m_currentID++;
        return m_currentID - 1;
    }

    bool AssetSubsystem::isValidID(uint32_t id)
    {
        return m_assets.contains(id);
    }

    AssetInfo& AssetSubsystem::getAsset(uint32_t id)
    {
        return m_assets.at(id);
    }

    void AssetSubsystem::destroyAsset(uint32_t id)
    {
        if (!m_assets.contains(id)) return;

        m_assets.erase(id);
    }
}
