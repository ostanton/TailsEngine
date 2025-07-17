#ifndef TAILS_ASSET_SUBSYSTEM_HPP
#define TAILS_ASSET_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/Handle.hpp>
#include <Tails/Assets/AssetType.hpp>
#include <Tails/Assets/AssetDeleter.hpp>
#include <Tails/String.hpp>
#include <Tails/Concepts.hpp>

#include <memory>
#include <type_traits>

namespace tails
{
    class IAsset;
    class IAssetLoader;
    struct SAssetPath;
}

/**
 * The assets namespace contains asset management struct, classes, and functions.
 * The asset subsystem manages alive assets, loading them from "somewhere" by calling the appropriate
 * loader function, in addition to destroying them when all references are dropped
 */
namespace tails::assets
{
    TAILS_API void init();
    TAILS_API void deinit();

    using LoadFileSignature = std::shared_ptr<IAsset>(*)(const CString&);
    using LoadMemorySignature = std::shared_ptr<IAsset>(*)(u8*, usize);
    TAILS_API void registerFileLoader(u8 assetType, LoadFileSignature function);
    TAILS_API void registerMemoryLoader(u8 assetType, LoadMemorySignature function);

    TAILS_API LoadFileSignature getFileLoader(u8 assetType);
    TAILS_API LoadMemorySignature getMemoryLoader(u8 assetType);

    /**
     * Loads an asset from file, relative to executable
     * @param assetType The asset's type
     * @param path Path to the file (relative to executable) to load
     * @return Shared pointer to loaded asset
     */
    TAILS_API std::shared_ptr<IAsset> loadAsset(u8 assetType, const CString& path);

    /**
     * Loads an asset from file, via an asset path object
     * @param assetPath The asset path
     * @return Shared pointer to loaded asset
     */
    TAILS_API std::shared_ptr<IAsset> loadAsset(const SAssetPath& assetPath);

    /**
     * Loads an asset from file, relative to executable
     * @tparam T Asset type
     * @param path Path to the file (relative to executable) to load
     * @return Shared pointer to loaded asset
     */
    template<DerivedFrom<IAsset> T>
    std::shared_ptr<T> loadAsset(const CString& path)
    {
        return std::static_pointer_cast<T>(
            loadAsset(getAssetType<T>(), path)
        );
    }

    /**
     * Gets an asset that is already loaded and exists in memory
     * @param handle Asset handle
     * @return Shared pointer to asset
     */
    TAILS_API std::shared_ptr<IAsset> getAsset(const SHandle& handle);
    TAILS_API bool validHandle(const SHandle& handle);

    std::shared_ptr<IAsset> allocateAsset(const std::shared_ptr<IAsset>& asset, const CString& path, u8 type);

    template<DerivedFrom<IAsset> T, typename... ArgsT>
    requires ConstructibleFrom<T, ArgsT...>
    std::shared_ptr<T> allocateAsset(const CString& path, ArgsT&&... args)
    {
        return std::static_pointer_cast<T>(
            allocateAsset(
                std::shared_ptr<T>(new T {std::forward<ArgsT>(args)...}, SAssetDeleter {}),
                path,
                getAssetType<T>()
            )
        );
    }
}

#endif // TAILS_ASSET_SUBSYSTEM_HPP
