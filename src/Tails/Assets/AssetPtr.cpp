#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Application.hpp>

namespace tails
{
    std::shared_ptr<IAsset> SAssetPath::load(CAssetManager* assetManager) const
    {
        return CAssetRegistry::get().loadAssetFromFile(
            assetType,
            path,
            assetManager != nullptr ? *assetManager : IApplication::get().getAssetManager()
        );
    }
}
