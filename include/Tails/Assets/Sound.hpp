#ifndef TAILS_SOUND_ASSET_HPP
#define TAILS_SOUND_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Asset.hpp>

namespace tails
{
    class TAILS_API CSound : public IAsset
    {
    public:
        [[nodiscard]] EAssetType getAssetType() const noexcept override;
    };
}

#endif // TAILS_SOUND_ASSET_HPP
