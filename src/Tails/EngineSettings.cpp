#include <Tails/EngineSettings.hpp>
#include <Tails/LevelSettings.hpp>
#include <Tails/Debug.hpp>

namespace tails
{
    SEngineSettings::SEngineSettings() = default;
    SEngineSettings::SEngineSettings(const SEngineSettings&) = default;
    SEngineSettings::SEngineSettings(SEngineSettings&&) noexcept = default;
    SEngineSettings& SEngineSettings::operator=(const SEngineSettings&) = default;
    SEngineSettings& SEngineSettings::operator=(SEngineSettings&&) noexcept = default;
    SEngineSettings::~SEngineSettings() = default;

    std::unique_ptr<SLevelSettings> SEngineSettings::createLevelSettings() const
    {
        return std::make_unique<SLevelSettings>();
    }
}
