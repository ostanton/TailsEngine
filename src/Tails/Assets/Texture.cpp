#include <Tails/Assets/Texture.hpp>
#include <Tails/Log.hpp>

#include <SDL3/SDL_render.h>

namespace tails
{
    CTexture::CTexture(
        const SVector2u size,
        const unsigned int channels,
        u8* pixels
    )
        : m_size(size)
        , m_channels(channels)
        , m_pixels(pixels)
    {}

    CTexture::CTexture(const CTexture& other)
        : IAsset(other)
        , m_size(other.m_size)
        , m_channels(other.m_channels)
    {
        m_pixels = static_cast<u8*>(SDL_malloc(other.getPixelCount()));
        SDL_memcpy(m_pixels, other.m_pixels, other.getPixelCount());
        m_internal = static_cast<SDL_Texture*>(SDL_malloc(sizeof(SDL_Texture)));
        SDL_memcpy(m_internal, other.m_internal, sizeof(SDL_Texture));
    }

    CTexture::CTexture(CTexture&& other) noexcept
        : m_size(other.m_size)
        , m_channels(other.m_channels)
        , m_pixels(other.m_pixels)
        , m_internal(other.m_internal)
    {
        other.m_size = 0;
        other.m_channels = 0;
        other.m_pixels = nullptr;
        other.m_internal = nullptr;
    }

    CTexture& CTexture::operator=(const CTexture& other)
    {
        if (this == &other)
            return *this;
        
        m_size = other.m_size;
        m_channels = other.m_channels;
        m_pixels = static_cast<u8*>(SDL_malloc(other.getPixelCount()));
        SDL_memcpy(m_pixels, other.m_pixels, other.getPixelCount());
        m_internal = static_cast<SDL_Texture*>(SDL_malloc(sizeof(SDL_Texture)));
        SDL_memcpy(m_internal, other.m_internal, sizeof(SDL_Texture));
        return *this;
    }

    CTexture& CTexture::operator=(CTexture&& other) noexcept
    {
        m_size = other.m_size;
        m_channels = other.m_channels;
        m_pixels = other.m_pixels;
        m_internal = other.m_internal;
        
        other.m_size = 0;
        other.m_channels = 0;
        other.m_pixels = nullptr;
        other.m_internal = nullptr;
        
        return *this;
    }

    CTexture::~CTexture()
    {
        if (m_pixels)
            SDL_free(m_pixels);
        
        if (m_internal)
            SDL_DestroyTexture(m_internal);
    }

    bool CTexture::operator==(const CTexture& other) const noexcept
    {
        // TODO - make better! Compare pixels?
        return m_size == other.m_size
            && m_channels == other.m_channels
            && m_pixels == other.m_pixels
            && getPixelCount() == other.getPixelCount()
            && m_internal == other.m_internal;
    }

    bool CTexture::operator!=(const CTexture& other) const noexcept
    {
        return !(*this == other);
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

    unsigned int CTexture::getPixelCount() const noexcept
    {
        return m_size.x * m_size.y * m_channels;
    }

    unsigned int CTexture::getPitch() const noexcept
    {
        const auto pitch = m_size.x * m_channels;
        return (pitch + 3) & ~3;
    }
}
