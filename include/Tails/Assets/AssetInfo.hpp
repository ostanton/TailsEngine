#ifndef TAILS_ASSETINFO_HPP
#define TAILS_ASSETINFO_HPP

#include <Tails/Config.hpp>

#include <string>
#include <memory>

namespace tails
{
    class Resource;
    class AssetSubsystem;
    class TextureResource;
    class SoundResource;
    class FontResource;
    class Engine;

    /**
     * A refactored structure created as a wrapper for a Resource and manages its lifetime.
     * This should be simple and straightforward, which is why I gutted the metadata & json loading stuff.
     * Can also be used just to reference an asset, like a piece of music that should be streamed and not loaded
     * into memory.
     */
    struct TAILS_API AssetInfo
    {
        friend AssetSubsystem;

        enum Category
        {
            Invalid = -1,
            Texture = 0,
            Sound,
            Font
        };

        AssetInfo() = delete;
        AssetInfo(Category category, const std::string& path, const Engine& engine);
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
                load();

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

        [[nodiscard]] Resource& getResource() const {return *m_resource;}
        [[nodiscard]] TextureResource& getTextureResource() const;
        [[nodiscard]] SoundResource& getSoundResource() const;
        [[nodiscard]] FontResource& getFontResource() const;

        /**
         * Load this asset's resource into memory
         * @return Load was successful
         */
        bool load();

        /**
         * Unloads this asset's resource from memory, freeing it
         */
        void unload();

        [[nodiscard]] const std::string& getPath() const {return m_path;}
        [[nodiscard]] Category getCategory() const {return m_category;}

        /**
         * Loads a resource of desired type
         * @tparam T Resource type to load
         * @return Whether loading was successful
         */
        template<typename T>
        bool loadResource()
        {
            static_assert(std::is_base_of_v<Resource, T>, "Failed to load resource, desired type does not derive Resource.");
            
            m_resource = std::make_unique<T>();
            return loadResource();
        }
        
    private:
        bool loadResource();

        /**
         * Path to resource, always relative to executable location via Engine's ini file
         */
        std::string m_path;

        /**
         * The category of this asset
         */
        Category m_category;

        /**
         * The resource data that is loaded or unloaded
         */
        std::unique_ptr<Resource> m_resource;
    };
}

#endif // TAILS_ASSETINFO_HPP
