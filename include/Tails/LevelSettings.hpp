#ifndef TAILS_LEVELSETTINGS_HPP
#define TAILS_LEVELSETTINGS_HPP

#include <Tails/Config.hpp>

#include <string>

namespace tails
{
    struct TAILS_API SLevelSettings
    {
        virtual ~SLevelSettings() = default;

        std::string name;
    };
}

#endif // TAILS_LEVELSETTINGS_HPP
