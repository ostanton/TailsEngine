#ifndef TAILS_ASSETSUBSYSTEM_HPP
#define TAILS_ASSETSUBSYSTEM_HPP

#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/AssetHandle.hpp>

#include <unordered_map>

namespace tails
{
    class TAILS_API AssetSubsystem : public Subsystem
    {
    public:
        uint32_t createAsset(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string& path);
        bool isValidID(uint32_t id);
        AssetInfo& getAsset(uint32_t id);
        void destroyAsset(uint32_t id);

    private:
        void init(Engine& engine) override {}
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        std::unordered_map<uint32_t, AssetInfo> m_assets;
        uint32_t m_currentID {0};
    };
}

#endif // TAILS_ASSETSUBSYSTEM_HPP
