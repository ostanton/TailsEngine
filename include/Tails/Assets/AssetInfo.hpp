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

    /**
     * A refactored structure created as a wrapper for a Resource and manages its lifetime.
     * This should be simple and straightforward, which is why I gutted the metadata & json loading stuff.
     * Can also be used just to reference an asset, like a piece of music that should be streamed and not loaded
     * into memory.
     */
    struct TAILS_API AssetInfo
    {
        friend AssetSubsystem;

        AssetInfo() = delete;
        explicit AssetInfo(std::string path);
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
        [[nodiscard]] TextureResource& getTexture() const;
        [[nodiscard]] SoundResource& getSound() const;
        [[nodiscard]] FontResource& getFont() const;

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

    private:
        template<typename T>
        bool loadResource()
        {
            m_resource = std::make_unique<T>();
            return loadResource();
        }

        bool loadResource();

        // path to source file (json, raw resource, etc.)
        std::string m_path;

        // can be loaded and unloaded when needed
        std::unique_ptr<Resource> m_resource;
    };
}

#endif // TAILS_ASSETINFO_HPP
