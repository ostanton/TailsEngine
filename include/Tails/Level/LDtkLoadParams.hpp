#ifndef TAILS_LDTK_LOAD_PARAMS_HPP
#define TAILS_LDTK_LOAD_PARAMS_HPP

#include <Tails/Config.hpp>
#include <Tails/Level/LoadParams.hpp>

#include <string>

namespace tails
{
    struct TAILS_API SLDtkLoadParams : SLoadParams
    {
        SLDtkLoadParams(
            std::filesystem::path inPath,
            std::string inWorld,
            std::string inLevel,
            std::string inLayer
        )
            : SLoadParams(std::move(inPath))
            , world(std::move(inWorld))
            , level(std::move(inLevel))
            , layer(std::move(inLayer))
        {}
        
        std::string world;
        std::string level;
        std::string layer;
    };
}

#endif // TAILS_LDTK_LOAD_PARAMS_HPP
