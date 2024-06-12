#include <Tails/Assets/AssetInfo.hpp>
#include <Tails/Assets/TextureResource.hpp>
#include <Tails/Assets/SoundResource.hpp>
#include <Tails/Assets/FontResource.hpp>
#include <Tails/Assert.hpp>
#include <Tails/Assets/Metadata/AssetMetadata.hpp>
#include <Tails/Assets/Metadata/SpriteMetadata.hpp>
#include <Tails/Assets/Metadata/SpritesheetMetadata.hpp>
#include <Tails/Assets/Metadata/TilemapMetadata.hpp>
#include <Tails/Assets/Metadata/SoundMetadata.hpp>

#include <nlohmann/json.hpp>
#include <fstream>

namespace tails
{
    AssetInfo::AssetInfo(std::string jsonPath)
            : m_jsonPath(std::move(jsonPath))
    {
        loadJson(m_jsonPath);
    }

    AssetInfo::AssetInfo(AssetInfo&& asset) noexcept
    {
        m_jsonPath = std::move(asset.m_jsonPath);
        m_resourceType = asset.m_resourceType;
        m_assetType = asset.m_assetType;
        m_metadata = std::move(asset.m_metadata);
        m_resource = std::move(asset.m_resource);
    }

    AssetInfo& AssetInfo::operator=(AssetInfo&& asset) noexcept
    {
        m_jsonPath = std::move(asset.m_jsonPath);
        m_resourceType = asset.m_resourceType;
        m_assetType = asset.m_assetType;
        m_metadata = std::move(asset.m_metadata);
        m_resource = std::move(asset.m_resource);
        return *this;
    }

    AssetInfo::~AssetInfo() = default;

    const AssetMetadata& AssetInfo::getMetadata()
    {
        // do we need an if first? no, right???
        // it is illegal to have an invalid metadata member.
        // every asset must have valid metadata
        TailsAssert(m_metadata, "Asset metadata is invalid!");

        return *m_metadata;
    }

    void AssetInfo::setData(
            AssetInfo::ResourceType resourceType,
            AssetInfo::AssetType assetType,
            std::string jsonPath)
    {
        m_resourceType = resourceType;
        m_assetType = assetType;
        m_jsonPath = std::move(jsonPath);
        loadJson(m_jsonPath);
    }

    bool AssetInfo::load()
    {
        // don't bother loading the memory if we have no metadata!
        // TODO - maybe load metadata here instead of returning false? or assert?
        if (!m_metadata) return false;

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

        return m_resource->load(m_metadata->path);
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

    std::string AssetInfo::assetTypeToString(AssetType type)
    {
        switch (type)
        {
            case AssetType::Invalid:
            default:
                return "invalid";
            case AssetType::Sprite:
                return "sprite";
            case AssetType::Spritesheet:
                return "spritesheet";
            case AssetType::Tilemap:
                return "tilemap";
            case AssetType::Music:
                return "music";
            case AssetType::Sound:
                return "sound";
            case AssetType::Font:
                return "font";
        }
    }

    AssetInfo::AssetType AssetInfo::stringToAssetType(const std::string& string)
    {
        if (string == "sprite")
            return AssetType::Sprite;
        else if (string == "spritesheet")
            return AssetType::Spritesheet;
        else if (string == "tilemap")
            return AssetType::Tilemap;
        else if (string == "music")
            return AssetType::Music;
        else if (string == "sound")
            return AssetType::Sound;
        else if (string == "font")
            return AssetType::Font;
        else
            return AssetType::Invalid;
    }

    AssetInfo::ResourceType AssetInfo::stringToResourceType(const std::string& string)
    {
        if (string == "texture")
            return ResourceType::Texture;
        else if (string == "sound")
            return ResourceType::Sound;
        else if (string == "font")
            return ResourceType::Font;
        else if (string == "shader")
            return ResourceType::Shader;
        else
            return ResourceType::Invalid;
    }

    bool AssetInfo::loadJson(const std::string& jsonPath)
    {
        // allocate new metadata memory of correct type based on json object key
        // set its default values

        std::ifstream stream {jsonPath};
        nlohmann::json obj {nlohmann::json::parse(stream)};

        for (auto& [key, value] : obj.items())
        {
            if (key == "category")
            {
                m_resourceType = stringToResourceType(value.get<std::string>());
                TailsAssert((m_resourceType == ResourceType::Invalid), "Invalid resource type!");
            }

            if (key == "type")
            {
                m_assetType = stringToAssetType(value.get<std::string>());
                TailsAssert((m_assetType == AssetType::Invalid), "Invalid asset type!");
            }

            switch (m_assetType)
            {
                case AssetType::Sprite:
                    loadSprite(key, value);
                    break;
                case AssetType::Spritesheet:
                    loadSpritesheet(key, value);
                    break;
                case AssetType::Tilemap:
                    loadTilemap(key, value);
                    break;
                case AssetType::Sound:
                case AssetType::Music:
                    loadSound(key, value);
                    break;
                case AssetType::Font:
                default:
                    return false;
            }

            TailsAssert(m_metadata, "Metadata is null after being allocated?!");

            if (key == "source")
                // TODO - make this be the path local to exec and not local to json file!!!
                m_metadata->path = value.get<std::string>();
        }

        return true;
    }

    void AssetInfo::loadSprite(const std::string& key, nlohmann::json& value)
    {
        m_metadata = std::make_unique<SpriteMetadata>();
        auto metadataPtr = dynamic_cast<SpriteMetadata*>(m_metadata.get());

        if (key == "smooth")
            metadataPtr->smooth = value.get<bool>();
    }

    void AssetInfo::loadSpritesheet(const std::string& key, nlohmann::json& value)
    {
        m_metadata = std::make_unique<SpritesheetMetadata>();
        auto metadataPtr = dynamic_cast<SpritesheetMetadata*>(m_metadata.get());
    }

    void AssetInfo::loadTilemap(const std::string& key, nlohmann::json& value)
    {
        m_metadata = std::make_unique<TilemapMetadata>();
        auto metadataPtr = dynamic_cast<TilemapMetadata*>(m_metadata.get());

        if (key == "grid-size")
        {
            for (auto& [sizeKey, sizeValue] : value.items())
            {
                if (sizeKey == "x")
                    metadataPtr->tileSize.x = sizeValue.get<int>();
                if (sizeKey == "y")
                    metadataPtr->tileSize.y = sizeValue.get<int>();
            }
        }
    }

    void AssetInfo::loadSound(const std::string& key, nlohmann::json& value)
    {
        m_metadata = std::make_unique<SoundMetadata>();
        auto metadataPtr = dynamic_cast<SoundMetadata*>(m_metadata.get());

        if (key == "loop")
            metadataPtr->loop = value.get<bool>();

        if (key == "start-offset")
            metadataPtr->startOffset = value.get<float>();

        if (key == "duration")
            metadataPtr->duration = value.get<float>();
    }
}
