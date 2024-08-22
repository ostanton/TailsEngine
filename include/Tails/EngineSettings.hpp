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

        [[nodiscard]] virtual std::string getSetupFilePath() const {return "engine.json";}

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

        [[nodiscard]] virtual std::unique_ptr<SLevelSettings> createLevelSettings() const;

    private:
        std::vector<std::unique_ptr<CClassRegistry>> m_registries;
    };
}

#endif // TAILS_ENGINESETTINGS_HPP
