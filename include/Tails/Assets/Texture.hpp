#ifndef TAILS_TEXTURE_ASSET_HPP
#define TAILS_TEXTURE_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Maths/Vector2.hpp>

struct SDL_Texture;

namespace tails
{
    class TAILS_API CTexture : public IAsset
    {
    public:
        CTexture(SVector2u size, unsigned int channels, u8* pixels);
        CTexture(const CTexture& other);
        CTexture(CTexture&& other) noexcept;
        CTexture& operator=(const CTexture& other);
        CTexture& operator=(CTexture&& other) noexcept;
        ~CTexture() override;

        [[nodiscard]] bool operator==(const CTexture& other) const noexcept;
        [[nodiscard]] bool operator!=(const CTexture& other) const noexcept;
        
        [[nodiscard]] EAssetType getAssetType() const noexcept override;

        [[nodiscard]] SVector2u getSize() const noexcept;
        [[nodiscard]] const u8* getPixels() const noexcept;
        [[nodiscard]] unsigned int getPixelCount() const noexcept;
        [[nodiscard]] unsigned int getPitch() const noexcept;

        bool setInternal(SDL_Texture* texture);
        [[nodiscard]] SDL_Texture* getInternal() const noexcept;

    private:
        SVector2u m_size;
        unsigned int m_channels; // bytes per pixel (RGBA, etc.)
        u8* m_pixels {nullptr}; // owning pixel data
        // TODO - specific format, etc. options too
        // TODO - instead of pointer here, create one texture with everything on? Like a batch or something
        SDL_Texture* m_internal {nullptr}; // owning pointer to SDL3's texture
    };

    template<>
    [[nodiscard]] constexpr u8 getAssetType<CTexture>()
    {
        return static_cast<u8>(EAssetType::Texture);
    }
}

#endif // TAILS_TEXTURE_ASSET_HPP
