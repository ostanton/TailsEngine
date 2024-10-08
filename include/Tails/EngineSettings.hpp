#ifndef TAILS_ENGINESETTINGS_HPP
#define TAILS_ENGINESETTINGS_HPP

#include <Tails/Config.hpp>

#include <string>
#include <memory>

namespace tails
{
    struct SLevelSettings;
    class CEngine;

    /**
     * Holds data for general engine setup and game-specific classes
     */
    struct TAILS_API SEngineSettings
    {
        friend CEngine;

        virtual ~SEngineSettings() = default;

        [[nodiscard]] virtual std::string getSetupFilePath() const {return "engine.json";}

        [[nodiscard]] virtual std::unique_ptr<SLevelSettings> createLevelSettings() const;
    };
}

#endif // TAILS_ENGINESETTINGS_HPP
