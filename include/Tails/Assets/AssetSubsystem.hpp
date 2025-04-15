#ifndef TAILS_ASSET_SUBSYSTEM_HPP
#define TAILS_ASSET_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Templated/Optional.hpp>
#include <Tails/Assets/Handle.hpp>
#include <Tails/Assets/AssetType.hpp>
#include <Tails/Assets/AssetDeleter.hpp>
#include <Tails/String.hpp>

#include <memory>
#include <type_traits>

namespace tails
{
    class IAsset;
    class IAssetLoader;
}

namespace tails::assets
{
    TAILS_API void init();
    TAILS_API void deinit();

    TAILS_API void registerLoader(std::unique_ptr<IAssetLoader> loader, u8 assetType, const char* debugName);

    namespace impl
    {
        template<typename T, typename = void>
        constexpr inline bool hasAssetType = false;
        template<typename T>
        constexpr inline bool hasAssetType<T, std::void_t<typename T::AssetType>> = true;
    }

    template<typename LoaderT>
    void registerLoader()
    {
        static_assert(impl::hasAssetType<LoaderT>, "Asset loader must have nested 'AssetType' alias");
        registerLoader(
            std::make_unique<LoaderT>(),
            getAssetType<typename LoaderT::AssetType>(),
            typeid(LoaderT).name()
        );
    }

    TAILS_API IAssetLoader* getLoader(u8 assetType);

    /**
     * Loads an asset from file
     * @param assetType The asset's type
     * @param path Path to the file to load
     * @return Shared pointer to loaded asset
     */
    TAILS_API std::shared_ptr<IAsset> loadAsset(u8 assetType, const CString& path);

    /**
     * Loads an asset from file
     * @tparam T Asset type
     * @param path Path to the file to load
     * @return Shared pointer to loaded asset
     */
    template<typename T>
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

    template<typename T, typename... ArgsT>
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
