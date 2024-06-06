#ifndef TAILS_ASSETMANAGER_HPP
#define TAILS_ASSETMANAGER_HPP

#include <Tails/Managers/Manager.hpp>
#include <Tails/Assets/Info.hpp>
#include <Tails/Assets/Handle.hpp>

#include <unordered_map>

namespace tails
{
    class AssetManager : public Manager
    {
    public:
        uint32_t createAsset(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string& path);
        bool isValidID(uint32_t id);
        AssetInfo& getAsset(uint32_t id);
        void destroyAsset(uint32_t id);

    private:
        void tick(float deltaTime) {}

        std::unordered_map<uint32_t, AssetInfo> m_assets;
        uint32_t m_currentID {0};
    };
}

#endif // TAILS_ASSETMANAGER_HPP
