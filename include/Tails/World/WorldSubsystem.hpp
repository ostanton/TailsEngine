#ifndef TAILS_WORLD_SUBSYSTEM_HPP
#define TAILS_WORLD_SUBSYSTEM_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class CRenderer;
    class CLevel;
    class CString;
}

namespace tails::world
{
    TAILS_API void init();
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render(const CRenderer& renderer);
    TAILS_API void cleanup();
    TAILS_API void deinit();
    TAILS_API CLevel* openLevel(const CString& path);
    TAILS_API void openLevel(std::shared_ptr<CLevel> level);
    TAILS_API CLevel* getCurrentLevel();
    TAILS_API CLevel* getTargetLevel();
}

#endif // TAILS_WORLD_SUBSYSTEM_HPP
