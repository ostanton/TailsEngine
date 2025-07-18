#include <Tails/World/WorldSubsystem.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/World/Actor.hpp>
#include <Tails/Log.hpp>
#include <Tails/String.hpp>
#include <Tails/Assets/AssetSubsystem.hpp>

#include <memory>

namespace tails::world
{
    namespace
    {
        /** Shared pointer to level asset in the asset subsystem */
        std::shared_ptr<CLevel> gCurrentLevel;
        /** Target level to make current at the end of this frame */
        std::shared_ptr<CLevel> gTargetLevel;
    }

    void init()
    {
        // open empty level
        TAILS_LOG(WorldSubsystem, Message, "Loading default empty level");
        gCurrentLevel = assets::loadAsset<CLevel>({});

        TAILS_LOG(WorldSubsystem, Message, "Initialised");
    }

    void tick(const float deltaSeconds)
    {
        gCurrentLevel->onTick(deltaSeconds);
    }

    void render()
    {
        gCurrentLevel->onRender();
    }

    void cleanup()
    {
        gCurrentLevel->cleanupActors();

        if (gTargetLevel)
        {
            gCurrentLevel = gTargetLevel;
            gTargetLevel.reset();
        }
    }

    void deinit()
    {
        gCurrentLevel.reset();
        gTargetLevel.reset();

        TAILS_LOG(WorldSubsystem, Message, "Deinitialised");
    }

    const std::shared_ptr<CLevel>& openLevel(const CString& path)
    {
        gTargetLevel = assets::loadAsset<CLevel>(path);
        return gTargetLevel;
    }

    void openLevel(std::shared_ptr<CLevel> level)
    {
        gTargetLevel = std::move(level);
    }

    std::shared_ptr<CLevel> getCurrentLevel()
    {
        return gCurrentLevel;
    }

    std::shared_ptr<CLevel> getTargetLevel()
    {
        return gTargetLevel;
    }
}
