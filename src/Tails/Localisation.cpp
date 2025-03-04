#include <Tails/Localisation.hpp>
#include <Tails/Maths/Maths.hpp>
#include <Tails/Containers/Map.hpp>

#include <fstream>
#include <nlohmann/json.hpp>

namespace tails::locale
{
    TMap<usize, std::string> gLocaleMap;

    const std::string& getLocalisedString(const usize id)
    {
        return gLocaleMap.at(id);
    }

    const std::string& getLocalisedString(const std::string_view id)
    {
        return getLocalisedString(hash(id));
    }

    bool loadLocalisedStrings(const std::filesystem::path& path)
    {
        std::ifstream file {path};

        if (!file.is_open())
            return false;

        const nlohmann::json localeObj = nlohmann::json::parse(file);

        if (localeObj.is_null())
            return false;

        gLocaleMap.clear();

        for (auto& [key, val] : localeObj.items())
        {
            if (val.is_string())
                gLocaleMap.try_emplace(hash(key), val.get<std::string>());
        }

        return true;
    }
}
