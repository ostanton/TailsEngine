#include <Tails/Assets/Texture.hpp>

namespace tails
{
    EAssetType CTexture::getAssetType() const noexcept
    {
        return EAssetType::Texture;
    }

    SVector2u CTexture::getSize() const noexcept
    {
        return m_size;
    }

    const u8* CTexture::getPixels() const noexcept
    {
        return m_pixels;
    }
}
