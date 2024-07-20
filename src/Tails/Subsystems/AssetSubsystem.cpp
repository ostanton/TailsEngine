#include <Tails/Subsystems/AssetSubsystem.hpp>

namespace tails
{
    AssetSubsystem::tempHandle AssetSubsystem::createAsset(const std::string& path)
    {
        m_assets.try_emplace(m_currentID, AssetInfo());
        m_assets[m_currentID].loadFromFile(path);
        ++m_currentID;
        return m_currentID - 1;
    }

    bool AssetSubsystem::isValidID(tempHandle id) const
    {
        return m_assets.contains(id);
    }

    const AssetInfo& AssetSubsystem::getAsset(tempHandle id) const
    {
        return m_assets.at(id);
    }

    AssetInfo& AssetSubsystem::getAsset(tempHandle id)
    {
        return m_assets.at(id);
    }

    void AssetSubsystem::destroyAsset(tempHandle id)
    {
        if (!m_assets.contains(id)) return;

        // TODO - might want preTick & postTick for things like this?
        m_assets.erase(id);
    }
}
