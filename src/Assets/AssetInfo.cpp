#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/TextureResource.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/FontResource.hpp>

namespace tails
{
    AssetInfo::AssetInfo(AssetInfo &&asset) noexcept
    {
        m_resourceType = asset.m_resourceType;
        m_assetType = asset.m_assetType;
        m_path = asset.m_path;
        m_resource = std::move(asset.m_resource);
    }

    AssetInfo &AssetInfo::operator=(AssetInfo &&asset) noexcept
    {
        m_resourceType = asset.m_resourceType;
        m_assetType = asset.m_assetType;
        m_path = asset.m_path;
        m_resource = std::move(asset.m_resource);
        return *this;
    }

    void AssetInfo::loadAutoSet(const std::string &path)
    {
        // auto set data from deciphering what kind of resource the file in path is?
    }

    void AssetInfo::setData(
            AssetInfo::ResourceType resourceType,
            AssetInfo::AssetType assetType,
            const std::string &path)
    {
        m_resourceType = resourceType;
        m_assetType = assetType;
        m_path = path;
    }

    bool AssetInfo::load()
    {
        switch (m_resourceType)
        {
            default:
                return false;
            case ResourceType::Texture:
                m_resource = std::make_unique<Texture>();
                break;
            case ResourceType::Sound:
                m_resource = std::make_unique<Sound>();
                break;
            case ResourceType::Font:
                m_resource = std::make_unique<Font>();
                break;
        }

        if (!m_resource) return false;

        return m_resource->load(m_path);
    }

    bool AssetInfo::load(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string &path)
    {
        setData(resourceType, assetType, path);
        return load();
    }

    void AssetInfo::unload()
    {
        // do nothing if the resource is already unloaded
        if (!isLoaded()) return;

        m_resource.reset();
    }
}
