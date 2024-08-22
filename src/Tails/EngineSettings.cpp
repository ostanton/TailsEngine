#include <Tails/EngineSettings.hpp>
#include <Tails/EngineRegistry.hpp>
#include <Tails/LevelSettings.hpp>

namespace tails
{
    SEngineSettings::SEngineSettings()
    {
        m_registries.emplace_back(std::make_unique<CEngineRegistry>());
    }

    std::unique_ptr<SLevelSettings>SEngineSettings::createLevelSettings() const
    {
        return std::make_unique<SLevelSettings>();
    }
}
