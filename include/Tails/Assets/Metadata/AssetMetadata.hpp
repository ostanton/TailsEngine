#ifndef TAILS_ASSETMETADATA_HPP
#define TAILS_ASSETMETADATA_HPP

#include <Tails/Config.hpp>

#include <string>

namespace tails
{
    struct TAILS_API AssetMetadata
    {
        virtual ~AssetMetadata() = default;

        // path to actual resource file (TODO - local?)
        std::string path;
    };
} // tails

#endif //TAILS_ASSETMETADATA_HPP
