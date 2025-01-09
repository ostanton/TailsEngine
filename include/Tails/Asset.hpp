#ifndef TAILS_ASSET_HPP
#define TAILS_ASSET_HPP

#include <Tails/Config.hpp>
#include <Tails/Concepts.hpp>
#include <Tails/Debug.hpp>
#include <Tails/ResourceManager.hpp>

#include <memory>
#include <filesystem>

namespace tails
{
    class IResource;

    /**
     * Wrapper for a resource which it auto-loads
     */
    template<Derives<IResource> ResT>
    class TAILS_API TAsset
    {
    public:
        TAsset() = delete;
        explicit TAsset(std::filesystem::path path)
            : m_path(std::move(path))
            , m_resource(CResourceManager::getOrLoadResource<ResT>(m_path))
        {
            if (!m_resource)
                CDebug::error("Asset failed to load resource, path: ", m_path);
        }
        TAsset(const TAsset&) = default;
        TAsset(TAsset&&) = default;
        TAsset& operator=(const TAsset&) = default;
        TAsset& operator=(TAsset&&) = default;
        ~TAsset() = default;

        [[nodiscard]] std::shared_ptr<ResT> getResource() const noexcept
        {
            if (!m_resource)
                return nullptr;

            return m_resource;
        }

        bool reload()
        {
            m_resource = CResourceManager::loadResource<ResT>(m_path);
            return m_resource;
        }

        void unload()
        {
            m_resource.reset();
        }

    private:
        std::filesystem::path m_path;
        std::shared_ptr<ResT> m_resource;
    };
}

#endif // TAILS_ASSET_HPP
