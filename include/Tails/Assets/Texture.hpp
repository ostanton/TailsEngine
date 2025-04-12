#ifndef TAILS_TEXTURE_ASSET_HPP
#define TAILS_TEXTURE_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    class TAILS_API CTexture : public IAsset
    {
    public:
        CTexture(SVector2u size, const u8* pixels);
        
        [[nodiscard]] EAssetType getAssetType() const noexcept override;

        [[nodiscard]] SVector2u getSize() const noexcept;
        [[nodiscard]] const u8* getPixels() const noexcept;

    private:
        SVector2u m_size;
        const u8* m_pixels {nullptr}; // dunno yet how to represent the pixels, etc.
        // TODO - specific format, etc. options too
    };

    template<>
    [[nodiscard]] constexpr u8 getAssetType<CTexture>()
    {
        return static_cast<u8>(EAssetType::Texture);
    }
}

#endif // TAILS_TEXTURE_ASSET_HPP
