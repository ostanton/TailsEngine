#ifndef TAILS_LOAD_PARAMS_HPP
#define TAILS_LOAD_PARAMS_HPP

#include <Tails/Config.hpp>

#include <filesystem>

namespace tails
{
    struct TAILS_API SLoadParams
    {
        SLoadParams(std::filesystem::path inPath)
            : path(std::move(inPath))
        {}
        
        std::filesystem::path path;
    };
}

#endif // TAILS_LOAD_PARAMS_HPP
