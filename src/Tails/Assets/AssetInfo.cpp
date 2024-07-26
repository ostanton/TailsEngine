#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/FontResource.hpp>
#include <Tails/Assets/Metadata/AssetMetadata.hpp>
#include <Tails/Assets/TextureResource.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    AssetInfo::AssetInfo(std::string path)
        : m_path(std::move(path))
    {}

    AssetInfo::AssetInfo(AssetInfo&& asset) noexcept
    {
        m_path = std::move(asset.m_path);
        m_resource = std::move(asset.m_resource);
    }

    AssetInfo& AssetInfo::operator=(AssetInfo&& asset) noexcept
    {
        m_path = std::move(asset.m_path);
        m_resource = std::move(asset.m_resource);
        return *this;
    }

    AssetInfo::~AssetInfo() = default;

    TextureResource* AssetInfo::getTexture() const
    {
        return getResource<TextureResource>();
    }

    SoundResource* AssetInfo::getSound() const
    {
        return getResource<SoundResource>();
    }

    FontResource* AssetInfo::getFont() const
    {
        return getResource<FontResource>();
    }

    bool AssetInfo::load()
    {
        if (!isLoaded())
        {
            if (loadResource<TextureResource>())
                return true;
            if (loadResource<SoundResource>())
                return true;
            if (loadResource<FontResource>())
                return true;

            return false;
        }

        return m_resource->load(m_path);
    }

    void AssetInfo::unload()
    {
        // do nothing if the resource is already unloaded
        if (!isLoaded()) return;

        m_resource.reset();
    }

    bool AssetInfo::loadResource()
    {
        return m_resource->load(m_path);
    }
}
