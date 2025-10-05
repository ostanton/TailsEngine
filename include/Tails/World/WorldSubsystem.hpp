#ifndef TAILS_WORLD_SUBSYSTEM_HPP
#define TAILS_WORLD_SUBSYSTEM_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails
{
    class CLevel;
    class CString;
}

namespace tails::world
{
    TAILS_API void init();
    TAILS_API void tick(float deltaSeconds);
    TAILS_API void render();
    TAILS_API void cleanup();
    TAILS_API void deinit();

    /**
     * Opens a level via its file path
     * @param path Relative level file path
     * @return Loaded level object
     */
    TAILS_API const std::shared_ptr<CLevel>& openLevel(const CString& path);

    /**
     * "Opens" an already loaded level, making it the target level to become current
     * @param level Target level to open
     */
    TAILS_API void openLevel(std::shared_ptr<CLevel> level);

    /**
     * Gets the currently loaded, active, level
     * @return Current level (can be null)
     */
    TAILS_API [[nodiscard]] const std::shared_ptr<CLevel>& getCurrentLevel();

    /**
     * Gets the target level, the level which we become the current level
     * next available time to set it (typically end of this frame)
     * @return Target level (normally null)
     */
    TAILS_API [[nodiscard]] const std::shared_ptr<CLevel>& getTargetLevel();
}

#endif // TAILS_WORLD_SUBSYSTEM_HPP
