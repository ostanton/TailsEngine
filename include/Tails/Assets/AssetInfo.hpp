#ifndef TAILS_ASSETINFO_HPP
#define TAILS_ASSETINFO_HPP

#include <Tails/Assets/Resource.hpp>

#include <string>
#include <memory>

namespace tails
{
    // a non-copyable, but moveable, class for holding resources and their metadata
    // could possibly have vector<Handle> for any asset dependencies
    // TODO - work with asset metadata json files
    struct AssetInfo
    {
        friend class AssetManager;

        enum class ResourceType
        {
            Texture,
            Sound,
            Font,
            Shader
        };

        enum class AssetType
        {
            Sprite,
            Spritesheet,
            Tilemap,
            Music,
            Sound,
            Font
        };

        AssetInfo() = default;
        AssetInfo(AssetInfo::ResourceType resourceType, AssetInfo::AssetType assetType, const std::string& path)
            : m_resourceType(resourceType), m_assetType(assetType), m_path(path) {}
        // delete copy constructor
        AssetInfo(const AssetInfo&) = delete;
        // move constructor
        AssetInfo(AssetInfo&& asset) noexcept
        {
            // TODO - will this work??
            *this = std::move(asset);
        }
        // delete copy-assignment operator
        AssetInfo& operator=(const AssetInfo&) = delete;
        // move assgnment operator
        AssetInfo& operator=(AssetInfo&& asset)
        {
            m_resourceType = asset.m_resourceType;
            m_assetType = asset.m_assetType;
            m_path = asset.m_path;
            m_resource = std::move(asset.m_resource);
            return *this;
        }
        ~AssetInfo() = default;

        bool isLoaded()
        {
            return m_resource != nullptr;
        }

        // do not return ref, resource could be null. See SFML docs, they return ptr with getters and want const refs for setters.
        template<typename T>
        T* getResource(bool loadIfUnavailable = false)
        {
            if (loadIfUnavailable)
            {
                if (!isLoaded())
                    load();
            }

            if (!m_resource) return nullptr;

            return static_cast<T*>(m_resource.get());
        }

        Resource* getBaseResource() {return m_resource.get();}

        ResourceType getResourceType() {return m_resourceType;}
        AssetType getAssetType() {return m_assetType;}
        const std::string& getResourcePath() {return m_path;}

        void loadAutoSet(const std::string& path)
        {
            // auto set data from deciphering what kind of resource the file in path is?
        }

        void setData(ResourceType resourceType, AssetType assetType, const std::string& path)
        {
            m_resourceType = resourceType;
            m_assetType = assetType;
            m_path = path;
        }

        // loads the asset's resource
        bool load();

        bool load(ResourceType resourceType, AssetType assetType, const std::string& path)
        {
            setData(resourceType, assetType, path);
            return load();
        }

        // unloads the assets' resource
        void unload()
        {
            // do nothing if the resource is already unloaded
            if (!isLoaded()) return;

            m_resource.reset();
        }

    private:
        ResourceType m_resourceType;
        AssetType m_assetType;
        std::string m_path;
        std::unique_ptr<Resource> m_resource;
    };
}

#endif // TAILS_ASSETINFO_HPP