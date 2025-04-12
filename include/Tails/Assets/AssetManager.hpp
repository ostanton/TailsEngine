#ifndef TAILS_ASSET_MANAGER_HPP
#define TAILS_ASSET_MANAGER_HPP

#include <Tails/Core.hpp>

#include <memory>
#include <vector>

namespace tails
{
    class IAsset;

    using SAssetHandle = usize;

    /**
     * The asset manager is a localised, non-owning, manager for assets created via the CAssetRegistry.
     * It does this by querying the registry, which calls the appropriate asset creator factory,
     * which returns an owning pointer to the loaded asset memory which the manager then assumes ownership of
     */
    class TAILS_API CAssetManager
    {
    public:
        void addAsset(const std::shared_ptr<IAsset>& asset);
        
    private:
        // TODO - std::map<SAssetHandle, std::weak_ptr<IAsset>>
        std::vector<std::weak_ptr<IAsset>> m_loadedAssets;
    };
}

#endif // TAILS_ASSET_MANAGER_HPP
