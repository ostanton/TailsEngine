#ifndef TAILS_ASSET_PTR_HPP
#define TAILS_ASSET_PTR_HPP

#include <Tails/Concepts.hpp>
#include <Tails/Assets/AssetPath.hpp>
#include <Tails/Assets/AssetManager.hpp>

#include <memory>

namespace tails
{
    class IAsset;

    /**
     * Extension of SAssetPath which caches its loaded asset for later use.
     * TODO - could have a constructor for an ID of some resource file stored in some map somewhere, json or registry maybe
     * @tparam T Asset type
     */
    template<Derives<IAsset> T>
    class TAssetPtr final
    {
    public:
        TAssetPtr() = default;
        TAssetPtr(SAssetPath path)
            : m_path(std::move(path))
        {}
        TAssetPtr(const TAssetPtr&) = default;
        TAssetPtr(TAssetPtr&&) noexcept = default;
        TAssetPtr& operator=(const TAssetPtr&) = default;
        TAssetPtr& operator=(TAssetPtr&&) = default;
        ~TAssetPtr() = default;

        void setPath(SAssetPath path)
        {
            m_path = std::move(path);
        }
        
        [[nodiscard]] std::shared_ptr<T> load() const
        {
            if (m_ptr)
                return m_ptr;

            m_ptr = m_path.load<T>();
            return m_ptr;
        }
        
    private:
        SAssetPath m_path;
        std::shared_ptr<T> m_ptr;
    };
}

#endif // TAILS_ASSET_PTR_HPP
