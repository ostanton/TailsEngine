#ifndef TAILS_WORLD_SUBSYSTEM_HPP
#define TAILS_WORLD_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Level.hpp>

namespace tails
{
    class IRenderer;
    class CLevel;
}

namespace tails::world
{
    using SLevelHandle = usize;
    
    TAILS_API void init();
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render(IRenderer& renderer);
    TAILS_API void cleanup();
    TAILS_API void deinit();
    TAILS_API SLevelHandle openLevel(const TAssetPtr<CLevelAsset>& level);
    TAILS_API CLevel* getLevelFromHandle(SLevelHandle handle);
}

#endif // TAILS_WORLD_SUBSYSTEM_HPP
