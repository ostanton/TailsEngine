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
        m_category = asset.m_category;
        m_type = asset.m_type;
        m_metadata = std::move(asset.m_metadata);
        m_resource = std::move(asset.m_resource);
    }

    AssetInfo& AssetInfo::operator=(AssetInfo&& asset) noexcept
    {
        m_jsonPath = std::move(asset.m_jsonPath);
        m_category = asset.m_category;
        m_type = asset.m_type;
        m_metadata = std::move(asset.m_metadata);
        m_resource = std::move(asset.m_resource);
        return *this;
    }

    AssetInfo::~AssetInfo() = default;

    const AssetMetadata& AssetInfo::getMetadata() const
    {
        // do we need an if first? no, right???
        // it is illegal to have an invalid metadata member.
        // every asset must have valid metadata
        TailsAssert(m_metadata, "Asset metadata is invalid!");

        return *m_metadata;
    }

    void AssetInfo::setData(Category category, Type type, std::string jsonPath)
    {
        m_category = category;
        m_type = type;
        m_jsonPath = std::move(jsonPath);
        loadJson(m_jsonPath);
    }

    bool AssetInfo::load()
    {
        // don't bother loading the memory if we have no metadata!
        // TODO - maybe load metadata here instead of returning false? or assert?
        if (!m_metadata) return false;

        switch (m_category)
        {
        default:
            std::cout << "Loading this category is not yet supported.\n";
            return false;
        case Category::Texture:
            m_resource = std::make_unique<Texture>();
            break;
        case Category::Sound:
            m_resource = std::make_unique<Sound>();
            break;
        case Category::Font:
            m_resource = std::make_unique<Font>();
            break;
        }

        if (!m_resource) return false;

        // TODO - accept Metadata type instead of string? Then the specific load methods can
        // cast to specific metadata types and set default values.
        return m_resource->load(m_metadata->path);
    }

    bool AssetInfo::load(Category category, Type type, const std::string &path)
    {
        setData(category, type, path);
        return load();
    }

    void AssetInfo::unload()
    {
        // do nothing if the resource is already unloaded
        if (!isLoaded()) return;

        m_resource.reset();
    }

    std::string AssetInfo::assetTypeToString(Type type)
    {
        switch (type)
        {
        default:
            return "invalid";
        case Type::Sprite:
            return "sprite";
        case Type::Spritesheet:
            return "spritesheet";
        case Type::Tilemap:
            return "tilemap";
        case Type::Music:
            return "music";
        case Type::Sound:
            return "sound";
        case Type::Font:
            return "font";
        }
    }

    AssetInfo::Type AssetInfo::stringToAssetType(const std::string& string)
    {
        if (string == "sprite")
            return Type::Sprite;
        if (string == "spritesheet")
            return Type::Spritesheet;
        if (string == "tilemap")
            return Type::Tilemap;
        if (string == "music")
            return Type::Music;
        if (string == "sound")
            return Type::Sound;
        if (string == "font")
            return Type::Font;
        
        return Type::Invalid;
    }

    std::string AssetInfo::assetCategoryToString(Category category)
    {
        switch (category)
        {
        case Category::Invalid:
        default:
            return "invalid";
        case Category::Texture:
            return "texture";
        case Category::Sound:
            return "sound";
        case Category::Font:
            return "font";
        case Category::Shader:
            return "shader";
        }
    }

    AssetInfo::Category AssetInfo::stringToAssetCategory(const std::string& string)
    {
        if (string == "texture")
            return Category::Texture;
        if (string == "sound")
            return Category::Sound;
        if (string == "font")
            return Category::Font;
        if (string == "shader")
            return Category::Shader;
        
        return Category::Invalid;
    }

    bool AssetInfo::loadJson(const std::string& jsonPath)
    {
        // allocate new metadata memory of correct type based on json object key
        // set its default values

        std::ifstream stream {"./" + jsonPath};
        nlohmann::json obj {nlohmann::json::parse(stream)};

        if (!obj)
        {
            std::cout << "Failed to load JSON asset file: " << jsonPath << "\n";
            return false;
        }

        for (auto& [key, value] : obj.items())
        {
            if (key == "category")
            {
                m_category = stringToAssetCategory(value.get<std::string>());
                TailsAssert((m_category == Category::Invalid), "Invalid resource type!");
            }

            if (key == "type")
            {
                m_type = stringToAssetType(value.get<std::string>());
                TailsAssert((m_type == Type::Invalid), "Invalid asset type!");
            }

            switch (m_type)
            {
            case Type::Sprite:
                loadSprite(key, value);
                break;
            case Type::Spritesheet:
                loadSpritesheet(key, value);
                break;
            case Type::Tilemap:
                loadTilemap(key, value);
                break;
            case Type::Music:
                loadMusic(key, value);
                break;
            case Type::Sound:
                loadSound(key, value);
                break;
            case Type::Font:
                loadFont(key, value);
                break;
            case Type::Invalid:
                std::cout << "Invalid asset type in: " << jsonPath << "\n";
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

    void AssetInfo::loadMusic(const std::string& key, nlohmann::json& value)
    {
        
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

    void AssetInfo::loadFont(const std::string& key, nlohmann::json& value)
    {
        
    }
}
