#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Application.hpp>

#include <iostream>

namespace tails
{
    std::shared_ptr<IAsset> SAssetPath::load(CAssetManager* assetManager) const
    {
        std::cout << "Loading asset!\n";
        return impl::CAssetRegistry::get().loadAssetFromFile(
            assetType,
            path,
            assetManager != nullptr ? *assetManager : IApplication::get().getAssetManager()
        );
    }
}
