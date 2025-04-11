#ifndef TAILS_LEVEL_ASSET_HPP
#define TAILS_LEVEL_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Asset.hpp>

namespace tails
{
    class TAILS_API CLevelAsset : public IAsset
    {
    public:
        [[nodiscard]] EAssetType getAssetType() const noexcept override {return EAssetType::Level;}
    };
}

#endif // TAILS_LEVEL_ASSET_HPP
