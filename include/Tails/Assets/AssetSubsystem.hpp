#ifndef TAILS_ASSET_SUBSYSTEM_HPP
#define TAILS_ASSET_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Templated/Optional.hpp>

#include <memory>

namespace tails
{
    class IAsset;
}

namespace tails::assets
{
    using SHandle = usize;
    
    TAILS_API void init();
    
    /**
     * Adds an asset to the asset subsystem. It does not check if it already exists, so this can be used to
     * "duplicate" assets if needed
     * @param asset Asset to add to the subsystem
     * @return Handle to the asset pointer
     */
    TAILS_API SHandle addAsset(const std::shared_ptr<IAsset>& asset);
    TAILS_API std::shared_ptr<IAsset> getAsset(SHandle handle);
    TAILS_API bool validHandle(SHandle handle);

    struct SAssetDeleter final
    {
        SHandle handle;
        void operator()(const IAsset* asset) const noexcept;
    };

    template<typename T, typename... ArgsT>
    std::shared_ptr<T> allocateAsset(ArgsT&&... args)
    {
        return std::shared_ptr<T>(new T {std::forward<ArgsT>(args)...}, SAssetDeleter {});
    }
}

#endif // TAILS_ASSET_SUBSYSTEM_HPP
