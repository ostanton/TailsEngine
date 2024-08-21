#include <Tails/EngineSettings.hpp>
#include <Tails/EngineRegistry.hpp>
#include <Tails/LevelSettings.hpp>

namespace tails
{
    SEngineSettings::SEngineSettings()
        : m_setupFilePath("engine.json"), m_levelSettings(std::make_unique<SLevelSettings>())
    {
        m_registries.emplace_back(std::make_unique<CEngineRegistry>());
    }
}
