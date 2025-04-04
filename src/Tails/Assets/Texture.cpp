#include <Tails/Assets/Texture.hpp>

namespace tails
{
    EAssetType CTexture::getAssetType() const noexcept
    {
        return EAssetType::Texture;
    }
}
