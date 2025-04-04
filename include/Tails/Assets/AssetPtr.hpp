#ifndef TAILS_ASSET_PTR_HPP
#define TAILS_ASSET_PTR_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetType.hpp>

#include <memory>

namespace tails
{
    class IAsset;
    class CAssetManager;

    /**
     * Wrapper for an asset type which can load whenever
     */
    struct TAILS_API SAssetPtr final
    {
        SAssetPtr(
            const EAssetType inAssetType
        )
            : assetType(static_cast<u8>(inAssetType))
        {}
        
        template<typename CustomAssetTypeT>
        SAssetPtr(
            const CustomAssetTypeT inCustomAssetType
        )
            : assetType(getCustomAssetID(inCustomAssetType))
        {}

        SAssetPtr(const IAsset& asset);

        u8 assetType;

        [[nodiscard]] std::shared_ptr<IAsset> load(const char* filename, CAssetManager* assetManager = nullptr) const;
    };

    /**
     * Refers to a specific asset on disk, and can load it
     */
    struct TAILS_API SAssetPath final
    {
        const char* filename;
        u8 assetType;
    };

    /**
     * Same as @code SAssetPtr@endcode, however it caches the loaded asset, and returns it as the correct type, instead
     * of the generic @code IAsset@endcode 
     * @tparam T Asset class
     *
     * TODO - have EAssetType be automatically set somehow??
     */
    template<typename T>
    class TAssetPtr final
    {
    public:
        explicit TAssetPtr(EAssetType assetType)
            : m_assetPtr(assetType)
        {}

        template<typename CustomAssetTypeT>
        explicit TAssetPtr(CustomAssetTypeT customAssetType)
            : m_assetPtr(customAssetType)
        {}

        explicit TAssetPtr(std::shared_ptr<T> asset)
            : m_assetPtr(*asset), m_cached(std::move(asset))
        {}

        explicit TAssetPtr(std::shared_ptr<T>&& asset)
            : m_assetPtr(*asset), m_cached(std::move(asset))
        {}

        TAssetPtr& operator=(std::shared_ptr<T>&& asset)
        {
            m_cached = std::move(asset);
            m_assetPtr = SAssetPtr {*m_cached};
            return *this;
        }
        
        [[nodiscard]] std::shared_ptr<T> load(const char* filename, CAssetManager* assetManager = nullptr) noexcept
        {
            if (!m_cached)
                m_cached = std::static_pointer_cast<T>(m_assetPtr.load(filename, assetManager));
            
            return m_cached;
        }
        
    private:
        SAssetPtr m_assetPtr;
        std::shared_ptr<T> m_cached;
    };
}

#endif // TAILS_ASSET_PTR_HPP
