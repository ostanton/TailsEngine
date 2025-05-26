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
        std::unordered_map<u8, LoadFileSignature> gFileLoaders;
        std::unordered_map<u8, LoadMemorySignature> gMemoryLoaders;
    }

    void init()
    {
        // register default engine asset loaders
        registerFileLoader(getAssetType(EAssetType::Texture), texture::load);
        registerFileLoader(getAssetType(EAssetType::Sound), sound::load);
        registerFileLoader(getAssetType(EAssetType::Level), level::load);

        registerMemoryLoader(getAssetType(EAssetType::Texture), texture::load);
        registerMemoryLoader(getAssetType(EAssetType::Sound), sound::load);
        registerMemoryLoader(getAssetType(EAssetType::Level), level::load);

        TAILS_LOG(AssetSubsystem, Message, "Initialised");
    }

    void deinit()
    {
        gFileLoaders.clear();
        gMemoryLoaders.clear();
        gLoadedAssets.clear();

        TAILS_LOG(AssetSubsystem, Message, "Deinitialised");
    }

    void registerFileLoader(u8 assetType, LoadFileSignature function)
    {
        gFileLoaders.emplace(assetType, function);
    }

    void registerMemoryLoader(u8 assetType, LoadMemorySignature function)
    {
        gMemoryLoaders.emplace(assetType, function);
    }

    LoadFileSignature getFileLoader(const u8 assetType)
    {
        if (gFileLoaders.contains(assetType))
            return gFileLoaders[assetType];

        return nullptr;
    }

    LoadMemorySignature getMemoryLoader(const u8 assetType)
    {
        if (gMemoryLoaders.contains(assetType))
            return gMemoryLoaders[assetType];

        return nullptr;
    }

    std::shared_ptr<IAsset> loadAsset(const u8 assetType, const CString& path)
    {
        CString fullPath = fs::getBasePath() + path;
        // if the path is already loaded as an asset, use it instead of loading a new one
        if (const SHandle handle = {fullPath.getData(), assetType}; validHandle(handle))
            return gLoadedAssets[handle].lock();
        
        auto const loader = getFileLoader(assetType);
        if (!loader)
        {
            TAILS_LOG(AssetSubsystem, Error, "Failed to find asset loader");
            return nullptr;
        }

        auto result = loader(fullPath);
        if (!result)
        {
            TAILS_LOG_VA(AssetSubsystem, Error, "Failed to load asset at path '{}'", fullPath.getData());
            return nullptr;
        }

        TAILS_LOG_VA(AssetSubsystem, Message, "Loaded asset at path '{}'", fullPath.getData());
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

        return gLoadedAssets.contains(handle);
    }

    void SAssetDeleter::operator()(const IAsset* asset) const noexcept
    {
        if (!validHandle(handle))
        {
            TAILS_LOG_VA(AssetSubsystem, Message, "Failed to delete asset with invalid handle '{}'", handle.getDebugPath().getData());
            return;
        }

        if (gLoadedAssets[handle].expired())
        {
            delete asset;
            gLoadedAssets.erase(handle);
            TAILS_LOG_VA(AssetSubsystem, Message, "Deleted asset with handle '{}'", handle.getDebugPath().getData());
        }
    }

    std::shared_ptr<IAsset> allocateAsset(
        const std::shared_ptr<IAsset>& asset,
        const CString& path,
        const u8 type
    )
    {
        gLastAssetIndex = SHandle {path, type};
        
        if (!gLoadedAssets.contains(gLastAssetIndex))
            gLoadedAssets.emplace(gLastAssetIndex, asset);
        else
            gLoadedAssets[gLastAssetIndex] = asset;
        
        std::get_deleter<SAssetDeleter>(asset)->handle = gLastAssetIndex;
        return asset;
    }
}
