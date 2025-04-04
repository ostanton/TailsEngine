#ifndef TAILS_ASSET_HPP
#define TAILS_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetType.hpp>

namespace tails
{
    /**
     * Abstract class representing any loaded asset (texture, sound, font, etc.).
     * It's loaded from disk/memory/etc. via its factory. This class serves as the memory itself,
     * and thus does not need to know how to load itself
     */
    class TAILS_API IAsset
    {
    public:
        IAsset() = default;
        IAsset(const IAsset&) = default;
        IAsset(IAsset&&) noexcept = default;
        IAsset& operator=(const IAsset&) = default;
        IAsset& operator=(IAsset&&) noexcept = default;
        virtual ~IAsset() = default;

        [[nodiscard]] virtual EAssetType getAssetType() const noexcept = 0;
        [[nodiscard]] virtual u8 getCustomAssetType() const noexcept {return 0;}
    };
}

#endif // TAILS_ASSET_HPP
