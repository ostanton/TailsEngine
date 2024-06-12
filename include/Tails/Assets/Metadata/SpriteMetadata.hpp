#ifndef TAILS_SPRITEMETADATA_HPP
#define TAILS_SPRITEMETADATA_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/Metadata/AssetMetadata.hpp>

namespace tails
{
    struct TAILS_API SpriteMetadata : AssetMetadata
    {
        bool smooth;
    };
} // tails

#endif //TAILS_SPRITEMETADATA_HPP
