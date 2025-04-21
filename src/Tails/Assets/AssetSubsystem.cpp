#include <Tails/Assets/AssetSubsystem.hpp>
#include <Tails/Assets/Loaders/TextureLoader.hpp>
#include <Tails/Assets/Loaders/SoundLoader.hpp>
#include <Tails/Assets/Loaders/LevelLoader.hpp>
#include <Tails/Assets/Asset.hpp>
#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Log.hpp>
#include <Tails/String.hpp>
#include <Tails/Filesystem.hpp>

#include <unordered_map>

namespace tails::assets
{
    namespace
    {
        SHandle gLastAssetIndex;
        std::unordered_map<SHandle, std::weak_ptr<IAsset>> gLoadedAssets;
        std::unordered_map<u8, std::unique_ptr<IAssetLoader>> gAssetLoaders;
    }

    void init()
    {
        // register default engine asset loaders
        registerLoader<CTextureLoader>();
        registerLoader<CSoundLoader>();
        registerLoader<CLevelLoader>();

        TAILS_LOG(AssetSubsystem, Message, "Initialised");
    }

    void deinit()
    {
        gAssetLoaders.clear();
        gLoadedAssets.clear();

        TAILS_LOG(AssetSubsystem, Message, "Deinitialised");
    }

    void registerLoader(std::unique_ptr<IAssetLoader> loader, const u8 assetType, const char* debugName)
    {
        const auto result = gAssetLoaders.try_emplace(assetType, std::move(loader));
        if (!result.second)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to register loader '%s'", debugName);
            return;
        }

        TAILS_LOG_VA(AssetSubsystem, Message, "Registered loader '%s'", debugName);
    }

    IAssetLoader* getLoader(const u8 assetType)
    {
        if (gAssetLoaders.find(assetType) != gAssetLoaders.end())
            return gAssetLoaders[assetType].get();

        return nullptr;
    }

    std::shared_ptr<IAsset> loadAsset(const u8 assetType, const CString& path)
    {
        CString fullPath = fs::getBasePath() + path;
        // if the path is already loaded as an asset, use it instead of loading a new one
        if (const SHandle handle = {fullPath.getData(), assetType}; validHandle(handle))
            return gLoadedAssets[handle].lock();
        
        auto const loader = getLoader(assetType);
        if (!loader)
        {
            TAILS_LOG(AssetSubsystem, Error, "Failed to find asset loader");
            return nullptr;
        }

        auto result = loader->load(fullPath);
        if (!result)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to load asset at path '%s'", fullPath.getData());
            return nullptr;
        }

        TAILS_LOG_VA(AssetSubsystem, Message, "Loaded asset at path '%s'", fullPath.getData());
        return result;
    }

    std::shared_ptr<IAsset> loadAsset(const SAssetPath& assetPath)
    {
        return loadAsset(assetPath.assetType, assetPath.path);
    }

    std::shared_ptr<IAsset> getAsset(const SHandle& handle)
    {
        if (validHandle(handle))
            return gLoadedAssets[handle].lock();

        return nullptr;
    }

    bool validHandle(const SHandle& handle)
    {
        if (!handle.isValid())
            return false;

        return gLoadedAssets.find(handle) != gLoadedAssets.end();
    }

    void SAssetDeleter::operator()(const IAsset* asset) const noexcept
    {
        if (!validHandle(handle))
        {
            TAILS_LOG_VA(AssetSubsystem, Message, "Failed to delete asset with invalid handle '%s'", handle.getDebugPath().getData());
            return;
        }

        if (gLoadedAssets[handle].expired())
        {
            delete asset;
            gLoadedAssets.erase(handle);
            TAILS_LOG_VA(AssetSubsystem, Message, "Deleted asset with handle '%s'", handle.getDebugPath().getData());
        }
    }

    std::shared_ptr<IAsset> allocateAsset(
        const std::shared_ptr<IAsset>& asset,
        const CString& path,
        const u8 type
    )
    {
        gLastAssetIndex = SHandle {path, type};
        
        if (gLoadedAssets.find(gLastAssetIndex) == gLoadedAssets.end())
            gLoadedAssets.emplace(gLastAssetIndex, asset);
        else
            gLoadedAssets[gLastAssetIndex] = asset;
        
        std::get_deleter<SAssetDeleter>(asset)->handle = gLastAssetIndex;
        return asset;
    }
}
