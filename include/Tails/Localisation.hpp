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
        using LocaleMap = std::unordered_map<size_t, std::string>;

        static LocaleMap& getLocaleMap();

        static const std::string& getLocalisedString(size_t id);
        static const std::string& getLocalisedString(std::string_view id);

        static constexpr size_t hash(std::string_view id)
        {
            // djb2 algorithm
            size_t result {5381};
            for (const char c : id)
            {
                result = (result << 5) + result + c;
            }
            return result;
        }

        static bool loadLocalisedStrings(const std::string& filename);

    private:
        CLocalisation() = default;

        static CLocalisation& get();
        
        LocaleMap m_localeMap;
    };
}

#endif // TAILS_LOCALISATION_HPP
