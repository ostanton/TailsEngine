#ifndef TAILS_ENGINESETTINGS_HPP
#define TAILS_ENGINESETTINGS_HPP

#include <Tails/Config.hpp>

#include <string>
#include <vector>
#include <memory>

namespace tails
{
    class CClassRegistry;
    struct SLevelSettings;
    class CEngine;

    /**
     * Holds data for general engine setup and game-specific classes
     */
    struct TAILS_API SEngineSettings
    {
        friend CEngine;

        SEngineSettings();

        [[nodiscard]] const std::string& getSetupFilePath() const {return m_setupFilePath;}

        template<typename T>
        [[nodiscard]] T* getRegistry() const
        {
            if (m_registries.empty()) return nullptr;

            for (auto& registry : m_registries)
            {
                if (auto castedRegistry = dynamic_cast<T*>(registry.get()))
                    return castedRegistry;
            }

            return nullptr;
        }

        template<typename T>
        [[nodiscard]] bool registryExists() const
        {
            return getRegistry<T>();
        }

        [[nodiscard]] SLevelSettings& getLevelSettings() const {return *m_levelSettings;}

    private:
        std::string m_setupFilePath;
        std::vector<std::unique_ptr<CClassRegistry>> m_registries;
        std::unique_ptr<SLevelSettings> m_levelSettings;
    };
}

#endif // TAILS_ENGINESETTINGS_HPP
