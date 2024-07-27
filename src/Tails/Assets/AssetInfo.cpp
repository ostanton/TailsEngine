#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/FontResource.hpp>
#include <Tails/Assets/TextureResource.hpp>
#include <Tails/Engine.hpp>

#include <nlohmann/json.hpp>

namespace tails
{
    AssetInfo::AssetInfo(Category category, const std::string& path, const Engine& engine)
        : m_category(category)
    {
        switch (category)
        {
        case Texture:
            m_path = engine.getFilePaths().textures + path;
            break;
        case Sound:
            m_path = engine.getFilePaths().sounds + path;
            break;
        case Font:
            m_path = engine.getFilePaths().fonts + path;
            break;
        case Invalid:
            // if invalid, treat the path like a normal path relative to the executable
            m_path = path;
            break;
        }
    }

    AssetInfo::AssetInfo(AssetInfo&& asset) noexcept
    {
        m_path = std::move(asset.m_path);
        m_resource = std::move(asset.m_resource);
        m_category = asset.m_category;
        asset.m_category = Invalid;
    }

    AssetInfo& AssetInfo::operator=(AssetInfo&& asset) noexcept
    {
        m_path = std::move(asset.m_path);
        m_resource = std::move(asset.m_resource);
        m_category = asset.m_category;
        asset.m_category = Invalid;
        return *this;
    }

    AssetInfo::~AssetInfo() = default;

    TextureResource& AssetInfo::getTextureResource() const
    {
        return *getResource<TextureResource>();
    }

    SoundResource& AssetInfo::getSoundResource() const
    {
        return *getResource<SoundResource>();
    }

    FontResource& AssetInfo::getFontResource() const
    {
        return *getResource<FontResource>();
    }

    bool AssetInfo::load()
    {
        if (!isLoaded())
        {
            switch (m_category)
            {
            case Texture:
                return loadResource<TextureResource>();
            case Sound:
                return loadResource<SoundResource>();
            case Font:
                return loadResource<FontResource>();
            case Invalid:
                return false;
            }
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
