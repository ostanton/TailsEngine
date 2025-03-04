#ifndef TAILS_LOCALISATION_HPP
#define TAILS_LOCALISATION_HPP

#include <Tails/Config.hpp>

#include <filesystem>
#include <string>

namespace tails::locale
{
    const std::string& getLocalisedString(usize id);
    const std::string& getLocalisedString(std::string_view id);
    bool loadLocalisedStrings(const std::filesystem::path& path);
}

#endif // TAILS_LOCALISATION_HPP
