#include <Tails/Assets/AssetManager.hpp>
#include <Tails/Instance.hpp>

namespace tails
{
    CAssetManager& CAssetManager::get()
    {
        return gInstance.assetManager;
    }
}
