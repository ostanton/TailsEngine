#ifndef TAILS_ASSET_TYPE_HPP
#define TAILS_ASSET_TYPE_HPP

#include <Tails/Core.hpp>

#include <type_traits>

namespace tails
{
    /**
     * User-defined asset types have their own IDs, starting from 0 (because they're offset by
     * EAssetType::Custom index). E.g.:
     * @code
     * enum class EMyAssetTypes : u8
     * {
     *     GIF,
     *     Video
     * };
     * @endcode
     * Video == 1, but with getAsset(EAssetType::Custom, EMyAssetTypes::Video) it becomes Custom + Video,
     * 4 + 1 = 5. So even though your custom type has a value of 1, the engine uses 5 instead as an offset to
     * the engine's default asset types.
     *
     * @note You shouldn't have more than one custom asset enumeration, because of how the offsets work. E.g.:
     * @code
     * enum class EMyAssets : u8 {VIDEO, UI}:
     * enum class EMyAssets2 : u8 {MUSIC, MESH};
     * @endcode
     * @code EMyAssets::VIDEO@endcode and@code EMyAssets2::MUSIC@endcode will return the same factory, and they
     * both have the integer value 0. So it's best to have one enumeration to keep all of your custom asset types.
     */
    enum class EAssetType : u8
    {
        Texture,
        Sound,
        Level,
        Font,
        // TODO - future types could include UI layouts (XML or my own DSL), etc.
        Custom // user-defined, this index + user-defined index == asset type ID
    };

    /**
     * Gets the asset type of the given asset (outside the asset class itself,
     * otherwise some allocation is required).
     * @return Asset ID value
     */
    template<typename>
    [[nodiscard]] constexpr u8 getAssetType();

    /**
     * Helper function to get any asset type as a u8
     * @tparam AssetTypeT Custom asset type enumeration
     * @param assetType Specific asset type enumerator
     * @return Asset ID value
     */
    template<typename AssetTypeT>
    [[nodiscard]] constexpr u8 getAssetType(const AssetTypeT assetType) noexcept
    {
        if constexpr (std::is_same_v<AssetTypeT, EAssetType>)
            return static_cast<u8>(assetType);
        else
            return static_cast<u8>(EAssetType::Custom) + static_cast<u8>(assetType);
    }
}

#endif // TAILS_ASSET_TYPE_HPP
