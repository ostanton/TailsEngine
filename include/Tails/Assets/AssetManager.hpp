#ifndef TAILS_ASSET_MANAGER_HPP
#define TAILS_ASSET_MANAGER_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetType.hpp>

#include <memory>
#include <vector>

namespace tails
{
    class IAsset;
    class CString;

    /**
     * The asset manager is a localised, owning, manager for assets created via the CAssetRegistry.
     * It does this by querying the registry, which calls the appropriate asset creator factory,
     * which returns an owning pointer to the loaded asset memory which the manager then assumes ownership of
     */
    class TAILS_API CAssetManager
    {
    public:
        std::shared_ptr<IAsset> getAsset(EAssetType type);
        
        template<typename CustomAssetTypeT>
        std::shared_ptr<IAsset> getAsset(CustomAssetTypeT customType)
        {
            return getAssetImpl(getCustomAssetID(customType));
        }
        
        std::shared_ptr<IAsset> getAsset(u8 assetID);
        
    private:
        // TODO - owning or not? can we check the ref-count and only destroy when it's == 1 with a shared_ptr and
        // not a weak_ptr?
        std::vector<std::weak_ptr<IAsset>> m_loadedAssets;
    };
}

#endif // TAILS_ASSET_MANAGER_HPP
