#ifndef TAILS_ASSET_DELETER_HPP
#define TAILS_ASSET_DELETER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Handle.hpp>

namespace tails
{
    class IAsset;
}

namespace tails::assets
{
    struct TAILS_API SAssetDeleter final
    {
        SHandle handle;
        void operator()(const IAsset* asset) const noexcept;
    };
}

#endif // TAILS_ASSET_DELETER_HPP
