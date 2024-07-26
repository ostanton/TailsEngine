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
        using tempHandle = size_t;
        
        tempHandle createAsset(const std::string& path, bool load = true);
        tempHandle createMusicAsset(const std::string& path);
        [[nodiscard]] bool isValidID(tempHandle id) const;
        [[nodiscard]] const AssetInfo& getAsset(tempHandle id) const;
        [[nodiscard]] AssetInfo& getAsset(tempHandle id);
        void destroyAsset(tempHandle id);

    private:
        void init(Engine& engine) override {}
        // TODO - could have a setting in the AssetInfo struct for "deleteIfUnloaded"
        // where the AssetInfo object gets erased from the map at the start of the next frame
        // if its resource is null?
        void tick(float deltaTime) override {}
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {}

        // could have some sort of linkage where assets are tied to the lifetime of specific objects?
        std::unordered_map<tempHandle, AssetInfo> m_assets;
        tempHandle m_currentID {0};
    };
}

#endif // TAILS_ASSETSUBSYSTEM_HPP
