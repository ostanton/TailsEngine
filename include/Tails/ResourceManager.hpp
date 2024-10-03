#ifndef TAILS_RESOURCE_MANAGER_HPP
#define TAILS_RESOURCE_MANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Debug.hpp>

#include <memory>
#include <unordered_map>
#include <string>
#include <exception>

namespace sf
{
    class Texture;
    class SoundBuffer;
    class Font;
}

namespace tails
{
    /**
     * Owns resources for various classes to have pointers to.
     * This allows SFML classes to be used with it (raw pointers to the resources that are managed by this manager)
     */
    class TAILS_API CResourceManager final
    {
    public:
        CResourceManager();
        CResourceManager(const CResourceManager&) = delete;
        CResourceManager(CResourceManager&&) noexcept = default;
        CResourceManager& operator=(const CResourceManager&) = delete;
        CResourceManager& operator=(CResourceManager&&) noexcept = default;
        ~CResourceManager();
        
        template<typename T>
        using TResource = std::unique_ptr<T>;

        template<typename T>
        using TResourceMap = std::unordered_map<std::string, TResource<T>>;

        sf::Texture* createTexture(const std::string& id, const std::string& filename);
        [[nodiscard]] sf::Texture* getTexture(const std::string& id) const;

        sf::SoundBuffer* createSound(const std::string& id, const std::string& filename);
        [[nodiscard]] sf::SoundBuffer* getSound(const std::string& id) const;

        sf::Font* createFont(const std::string& id, const std::string& filename);
        [[nodiscard]] sf::Font* getFont(const std::string& id) const;

    private:
        template<typename T>
        T* createResource(const std::string& id, const std::string& path, TResourceMap<T>& dataMap)
        {
            if (!dataMap.contains(id))
            {
                try {dataMap.try_emplace(id, std::make_unique<T>(path));}
                catch (const std::exception& e)
                {
                    CDebug::error("Failed to create resource, exception: ", e.what());
                    return nullptr;
                }
                
                CDebug::print("Created \"", id, "\" resource at \"", path, "\"");
            }
            else
            {
                CDebug::print("Resource \"", id, "\" already exists, getting it");
            }
            
            return dataMap[id].get();
        }

        template<typename T>
        [[nodiscard]] T* getResource(const std::string& id, const TResourceMap<T>& dataMap) const
        {
            if (!dataMap.contains(id))
            {
                CDebug::error("Failed to find \"", id, "\" resource");
                return nullptr;
            }

            return dataMap.at(id).get();
        }
        
        TResourceMap<sf::Texture> m_textures;
        TResourceMap<sf::SoundBuffer> m_sounds;
        TResourceMap<sf::Font> m_fonts;
    };
}

#endif // TAILS_RESOURCE_MANAGER_HPP
