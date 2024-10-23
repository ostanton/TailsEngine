#include <Tails/Localisation.hpp>
#include <Tails/Maths.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails
{
    CLocalisation::LocaleMap& CLocalisation::getLocaleMap()
    {
        return get().m_localeMap;
    }

    const std::string& CLocalisation::getLocalisedString(size_t id)
    {
        return getLocaleMap().at(id);
    }

    const std::string& CLocalisation::getLocalisedString(std::string_view id)
    {
        return getLocalisedString(hash(id));
    }

    bool CLocalisation::loadLocalisedStrings(const std::string& filename)
    {
        std::ifstream file {filename};
        
        if (!file.is_open()) return false;
        
        nlohmann::json localeObj = nlohmann::json::parse(file);

        if (localeObj.is_null()) return false;
        
        LocaleMap& locMap {getLocaleMap()};
        locMap.clear();

        for (auto& [locKey, locVal] : localeObj.items())
        {
            if (locVal.is_string())
                locMap.try_emplace(hash(locKey), locVal.get<std::string>());
        }

        return true;
    }

    CLocalisation& CLocalisation::get()
    {
        static CLocalisation instance;
        return instance;
    }
}
