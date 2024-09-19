#include <Tails/EngineSettings.hpp>
#include <Tails/LevelSettings.hpp>

namespace tails
{
    std::unique_ptr<SLevelSettings>SEngineSettings::createLevelSettings() const
    {
        return std::make_unique<SLevelSettings>();
    }
}
