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
        [[nodiscard]] EAssetType getAssetType() const noexcept override;

        [[nodiscard]] SVector2u getSize() const noexcept;
        [[nodiscard]] const u8* getPixels() const noexcept;

    private:
        SVector2u m_size;
        const u8* m_pixels {nullptr};
        // TODO - specific format, etc. options too
    };
}

#endif // TAILS_TEXTURE_ASSET_HPP
