#ifndef TAILS_ASSETSUBSYSTEM_HPP
#define TAILS_ASSETSUBSYSTEM_HPP

#include <Tails/Config.hpp>
#include <Tails/Subsystems/Subsystem.hpp>
#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/AssetHandle.hpp>

#include <unordered_map>

namespace tails
{
    class TAILS_API AssetSubsystem final : public Subsystem
    {
    public:
        uint32_t createAsset(const std::string& path);
        bool isValidID(uint32_t id);
        AssetInfo& getAsset(uint32_t id);
        void destroyAsset(uint32_t id);

    private:
        void init(Engine& engine) override {}
        // TODO - could have a setting in the AssetInfo struct for "deleteIfUnloaded"
        // where the AssetInfo object gets erased from the map at the start of the next frame
        // if its resource is null?
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        // could have some sort of linkage where assets are tied to the lifetime of specific objects?
        std::unordered_map<uint32_t, AssetInfo> m_assets;
        uint32_t m_currentID {0};
    };
}

#endif // TAILS_ASSETSUBSYSTEM_HPP
