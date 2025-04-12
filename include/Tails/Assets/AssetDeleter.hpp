#ifndef TAILS_ASSET_DELETER_HPP
#define TAILS_ASSET_DELETER_HPP

#include <Tails/Core.hpp>

#include <vector>

namespace tails
{
    class IAsset;
    class CAssetManager;

    /**
     * Stateful deleter for assets, which knows which asset managers are referencing it,
     * so can erase its own entry in said asset managers
     */
    struct TAILS_API SAssetDeleter final
    {
        void operator()(const IAsset* asset) const noexcept;

        // asset managers we want to remove this asset's entry from
        std::vector<CAssetManager*> assetManagers;
    };
}

#endif // TAILS_ASSET_DELETER_HPP
