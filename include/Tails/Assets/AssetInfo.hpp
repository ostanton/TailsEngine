#ifndef TAILS_ASSETINFO_HPP
#define TAILS_ASSETINFO_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/Resource.hpp>

#include <nlohmann/json_fwd.hpp>

#include <string>
#include <memory>

namespace tails
{
    struct AssetMetadata;

    // a non-copyable, but moveable, class for holding resources and their metadata
    // could possibly have vector<Handle> for any asset dependencies
    // TODO - work with asset metadata json files
    struct TAILS_API AssetInfo
    {
        friend class AssetManager;

        enum class ResourceType
        {
            Invalid = -1,
            Texture = 0,
            Sound,
            Font,
            Shader
        };

        enum class AssetType
        {
            Invalid = -1,
            Sprite = 0,
            Spritesheet,
            Tilemap,
            Music,
            Sound,
            Font
        };

        AssetInfo() = delete;
        explicit AssetInfo(std::string jsonPath);
        // delete copy constructor
        AssetInfo(const AssetInfo&) = delete;
        // move constructor
        AssetInfo(AssetInfo&& asset) noexcept;
        // delete copy-assignment operator
        AssetInfo& operator=(const AssetInfo&) = delete;
        // move assignment operator
        AssetInfo& operator=(AssetInfo&& asset) noexcept;

        ~AssetInfo();

        bool isLoaded() {return m_resource != nullptr;}

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
        const AssetMetadata& getMetadata();

        void setData(ResourceType resourceType, AssetType assetType, std::string path);

        // loads the asset's resource
        bool load();
        bool load(ResourceType resourceType, AssetType assetType, const std::string& path);

        // unloads the assets' resource
        void unload();

        static std::string assetTypeToString(AssetType type);
        static AssetType stringToAssetType(const std::string& string);

        static ResourceType stringToResourceType(const std::string& string);

    private:
        bool loadJson(const std::string& jsonPath);
        void loadSprite(const std::string& key, nlohmann::json& value);
        void loadSpritesheet(const std::string& key, nlohmann::json& value);
        void loadTilemap(const std::string& key, nlohmann::json& value);
        void loadSound(const std::string& key, nlohmann::json& value);

        // set in constructor
        std::string m_jsonPath;

        // set after loading json metadata using m_jsonPath
        ResourceType m_resourceType {ResourceType::Invalid};
        AssetType m_assetType {AssetType::Invalid};
        std::unique_ptr<AssetMetadata> m_metadata;

        // can be loaded and unloaded when needed
        std::unique_ptr<Resource> m_resource;
    };
}

#endif // TAILS_ASSETINFO_HPP
