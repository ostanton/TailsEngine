#ifndef TAILS_LOCALISATION_HPP
#define TAILS_LOCALISATION_HPP

#include <Tails/Config.hpp>

#include <unordered_map>
#include <string>

namespace tails
{
    class TAILS_API CLocalisation final
    {
    public:
        using LocaleMap = std::unordered_map<int, std::string>;

        static LocaleMap& getLocaleMap();

        static const std::string& getLocalisedString(int id);
        static const std::string& getLocalisedString(std::string_view id);

        static constexpr int hash(std::string_view id)
        {
            return 0;
        }

        static bool loadLocalisedStrings(const std::string& filename);

    private:
        CLocalisation() = default;

        static CLocalisation& get();
        
        LocaleMap m_localeMap;
    };
}

#endif // TAILS_LOCALISATION_HPP
