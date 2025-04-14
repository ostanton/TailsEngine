#include <Tails/Assets/Texture.hpp>

namespace tails
{
    CTexture::CTexture(
        const SVector2u size,
        const unsigned int channels,
        const u8* pixels
    )
        : m_size(size)
        , m_channels(channels)
        , m_pixels(pixels)
    {
    }

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

    unsigned int CTexture::getImageSize() const noexcept
    {
        return m_size.x * m_size.y * m_channels;
    }

    unsigned int CTexture::getPitch() const noexcept
    {
        const auto pitch = m_size.x * m_channels;
        return (pitch + 3) & ~3;
    }
}
