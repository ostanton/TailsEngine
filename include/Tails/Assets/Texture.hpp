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

    private:
        SVector2u m_size;
    };
}

#endif // TAILS_TEXTURE_ASSET_HPP
