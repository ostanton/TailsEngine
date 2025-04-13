#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Assets/AssetRegistry.hpp>
#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Loaders/SoundLoader.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Log.hpp>

#include <unordered_map>

namespace tails::assets
{
    namespace
    {
        // 0 is reserved for invalid handle
        SHandle gLastAssetIndex {0};
        std::unordered_map<SHandle, std::weak_ptr<IAsset>> gLoadedAssets;
    }
    
    void init()
    {
        // register default engine asset loaders
        auto& registry = impl::CAssetRegistry::get();
        registry.registerLoader<CTextureLoader>(getAssetType(EAssetType::Texture));
        registry.registerLoader<CSoundLoader>(getAssetType(EAssetType::Sound));
    }

    SHandle addAsset(const std::shared_ptr<IAsset>& asset)
    {
        gLastAssetIndex++;
        gLoadedAssets[gLastAssetIndex] = asset;
        std::get_deleter<SAssetDeleter>(asset)->handle = gLastAssetIndex;
        return gLastAssetIndex;
    }

    std::shared_ptr<IAsset> getAsset(const SHandle handle)
    {
        if (gLoadedAssets.find(handle) != gLoadedAssets.end())
            return gLoadedAssets[handle].lock();

        return nullptr;
    }

    bool validHandle(const SHandle handle)
    {
        if (handle == 0)
            return false;
        
        return gLoadedAssets.find(handle) != gLoadedAssets.end();
    }

    void SAssetDeleter::operator()(const IAsset* asset) const noexcept
    {
        if (validHandle(handle))
        {
            gLoadedAssets.erase(handle);
            TAILS_LOG(AssetSubsystem, Message, "Deleted asset with handle '%d'", handle);
        }
        else
            TAILS_LOG(AssetSubsystem, Message, "Failed to delete asset with invalid handle '%d'", handle);

        delete asset;
    }
}
