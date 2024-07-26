#ifndef TAILS_ASSETINFO_HPP
#define TAILS_ASSETINFO_HPP

#include <Tails/Config.hpp>

#include <nlohmann/json_fwd.hpp>

#include <string>
#include <memory>

namespace tails
{
    struct AssetMetadata;
    class Resource;
    class AssetSubsystem;
    class Texture;
    class Sound;
    class Font;

    // a non-copyable, but moveable, class for holding resources and their metadata
    // could possibly have vector<Handle> for any asset dependencies
    struct TAILS_API AssetInfo
    {
        friend AssetSubsystem;
        
        enum class Category
        {
            Invalid = -1,
            Texture = 0,  // defaults to Type::Sprite
            Sound,        // defaults to Type::Sound
            Font,         // defaults to Type::Font
            Shader
        };

        enum class Type
        {
            Invalid = -1,
            Sprite = 0,   // Category::Texture
            Spritesheet,  // Category::Texture
            Tilemap,      // Category::Texture
            Music,        // Category::Sound
            Sound,        // Category::Sound
            Font          // Category::Font
        };

        AssetInfo();
        // delete copy constructor
        AssetInfo(const AssetInfo&) = delete;
        // move constructor
        AssetInfo(AssetInfo&& asset) noexcept;
        // delete copy-assignment operator
        AssetInfo& operator=(const AssetInfo&) = delete;
        // move assignment operator
        AssetInfo& operator=(AssetInfo&& asset) noexcept;

        ~AssetInfo();

        [[nodiscard]] bool isLoaded() const {return m_resource != nullptr;}

        // do not return ref, resource could be null. See SFML docs, they return ptr with getters and want const refs for setters.
        template<typename T>
        [[nodiscard]] T* getResource(bool loadIfUnavailable = false)
        {
            static_assert(std::is_base_of_v<Resource, T>,
                "Failed to get resource, desired type does not derive Resource.");
            
            if (loadIfUnavailable)
            {
                if (!isLoaded())
                    load();
            }

            if (!m_resource) return nullptr;

            return static_cast<T*>(m_resource.get());
        }

        template<typename T>
        [[nodiscard]] T* getResource() const
        {
            static_assert(std::is_base_of_v<Resource, T>,
                "Failed to get resource, desired type does not derive Resource.");
            
            if (!m_resource) return nullptr;

            return static_cast<T*>(m_resource.get());
        }

        [[nodiscard]] Resource* getResource() const {return m_resource.get();}
        [[nodiscard]] Texture* getTexture() const;
        [[nodiscard]] Sound* getSound() const;
        [[nodiscard]] Font* getFont() const;

        [[nodiscard]] Category getCategory() const {return m_category;}
        [[nodiscard]] Type getType() const {return m_type;}
        [[nodiscard]] const AssetMetadata& getMetadata() const;

        template<typename T>
        [[nodiscard]] const T& getMetadata() const
        {
            static_assert(std::is_base_of_v<AssetMetadata, T>,
                    "Failed to get metadata, desired target type does not derive AssetMetadata");
            return *dynamic_cast<T*>(m_metadata.get());
        }

        void setData(Category category, Type type, std::string path);

        // loads the asset's resource
        bool load();
        bool load(Category category, Type type, const std::string& path);

        // unloads the assets' resource
        void unload();

        [[nodiscard]] static std::string assetTypeToString(Type type);
        [[nodiscard]] static Type stringToAssetType(const std::string& string);

        [[nodiscard]] static std::string assetCategoryToString(Category category);
        [[nodiscard]] static Category stringToAssetCategory(const std::string& string);

    private:
        /* Load from file methods */
        
        bool loadFromFile(const std::string& path);
        bool loadJson(const std::string& jsonPath);

        /* Load metadata from json methods */
        
        void loadSprite(const std::string& key, nlohmann::json& value);
        void loadSpritesheet(const std::string& key, nlohmann::json& value);
        void loadTilemap(const std::string& key, nlohmann::json& value);
        void loadMusic(const std::string& key, nlohmann::json& value);
        void loadSound(const std::string& key, nlohmann::json& value);
        void loadFont(const std::string& key, nlohmann::json& value);

        /**
         * Gets a file's category based on its extension
         * @param extension File extension
         * @return File's category
         */
        static Category getCategoryFromExtension(const std::string& extension);

        // path to source file (json, raw resource, etc.)
        std::string m_path;

        // set after loading json metadata using m_jsonPath
        Category m_category {Category::Invalid};
        Type m_type {Type::Invalid};
        std::unique_ptr<AssetMetadata> m_metadata;

        // can be loaded and unloaded when needed
        std::unique_ptr<Resource> m_resource;
    };
}

#endif // TAILS_ASSETINFO_HPP
