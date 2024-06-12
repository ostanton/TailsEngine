#ifndef TAILS_SOUNDMETADATA_HPP
#define TAILS_SOUNDMETADATA_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/Metadata/AssetMetadata.hpp>

namespace tails
{
    struct TAILS_API SoundMetadata : AssetMetadata
    {
        bool loop;
        float startOffset;
        float duration;
    };
}

#endif //TAILS_SOUNDMETADATA_HPP
