#ifndef TAILS_ASSETMETADATA_HPP
#define TAILS_ASSETMETADATA_HPP

#include <Tails/Config.hpp>

#include <string>

namespace tails
{
    struct TAILS_API AssetMetadata
    {
        virtual ~AssetMetadata() = default;

        std::string path;
    };
} // tails

#endif //TAILS_ASSETMETADATA_HPP
