#ifndef TAILS_ASSET_PTR_HPP
#define TAILS_ASSET_PTR_HPP

#include <Tails/Core.hpp>
#include <Tails/Assets/AssetType.hpp>
#include <Tails/String.hpp>

#include <memory>

namespace tails
{
    class IAsset;
    class CAssetManager;

    /**
     * Refers to a specific asset on disk, and can load it. Acts like a "soft" asset pointer
     */
    struct TAILS_API SAssetPath final
    {
        SAssetPath(u8 inAssetType, CString inPath = {});
        template<typename AssetTypeT>
        SAssetPath(const AssetTypeT inAssetType, CString inPath = {})
            : assetType(getAssetType(inAssetType)), path(std::move(inPath))
        {}

        u8 assetType;
        /** Path relative to executable */
        CString path;

        [[nodiscard]] std::shared_ptr<IAsset> load() const;
        [[nodiscard]] CString getFullPath() const;
    };

    /**
     * Same as @code SAssetPtr@endcode, however it caches the loaded asset, and returns it as the correct type, instead
     * of the generic @code IAsset@endcode 
     * @tparam T Asset class
     */
    template<typename T>
    class TAssetPtr final
    {
    public:
        explicit TAssetPtr()
            : m_assetPath(getAssetType<T>())
        {}
        explicit TAssetPtr(CString path)
            : m_assetPath(getAssetType<T>(), std::move(path))
        {}

        TAssetPtr& operator=(std::shared_ptr<T>&& asset)
        {
            m_cached = std::move(asset);
            m_assetPath = SAssetPath {*m_cached};
            return *this;
        }

        void setPath(const char* path) noexcept {m_assetPath.path = path;}
        [[nodiscard]] const SAssetPath& getAssetPath() const noexcept {return m_assetPath;}
        
        [[nodiscard]] std::shared_ptr<T> load() noexcept
        {
            if (!m_cached)
                m_cached = std::static_pointer_cast<T>(m_assetPath.load());
            
            return m_cached;
        }
        
    private:
        SAssetPath m_assetPath;
        std::shared_ptr<T> m_cached;
    };
}

#endif // TAILS_ASSET_PTR_HPP
