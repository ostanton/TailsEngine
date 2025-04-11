#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/World/Actor.hpp>

#include <unordered_map>

namespace tails::world
{
    namespace
    {
        usize gNextLevelIndex {0};
        std::unordered_map<usize, CLevel> gLevels;
    }
    
    void init()
    {
        const TAssetPtr<CLevelAsset> nullLevel {EAssetType::Level};
        openLevel(nullLevel);
    }

    void tick(const float deltaSeconds)
    {
        for (auto& [index, level] : gLevels)
        {
            level.onTick(deltaSeconds);
        }
    }

    void render(IRenderer& renderer)
    {
        for (auto& [index, level] : gLevels)
        {
            renderer.render(level);
        }
    }

    void cleanup()
    {
        for (auto& [index, level] : gLevels)
        {
            level.cleanupActors();
        }
    }

    SLevelHandle openLevel(const TAssetPtr<CLevelAsset>& level)
    {
        // TODO - open level from the level asset
        gLevels.try_emplace(gNextLevelIndex++);
        return gNextLevelIndex - 1;
    }

    CLevel* getLevelFromHandle(const SLevelHandle handle)
    {
        if (gLevels.find(handle) != gLevels.end())
            return &gLevels[handle];
        
        return nullptr;
    }
}
