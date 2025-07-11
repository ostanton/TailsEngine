#ifndef TAILS_SOUND_ASSET_HPP
#define TAILS_SOUND_ASSET_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Asset.hpp>

typedef struct SDL_AudioStream SDL_AudioStream;

namespace tails
{
    class TAILS_API CSound : public IAsset
    {
    public:
        [[nodiscard]] EAssetType getAssetType() const noexcept override;

    private:
        [[maybe_unused]] SDL_AudioStream* m_internal {nullptr};
    };

    template<>
    [[nodiscard]] constexpr u8 getAssetType<CSound>()
    {
        return static_cast<u8>(EAssetType::Sound);
    }
}

#endif // TAILS_SOUND_ASSET_HPP
