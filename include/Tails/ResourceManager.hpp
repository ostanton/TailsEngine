#ifndef TAILS_RESOURCEMANAGER_HPP
#define TAILS_RESOURCEMANAGER_HPP

#include <Tails/Config.hpp>
#include <Tails/Debug.hpp>

#include <SFML/System/Exception.hpp>

#include <memory>
#include <unordered_map>
#include <string>

namespace sf
{
    class Texture;
    class SoundBuffer;
    class Font;
}

namespace tails
{
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
                catch (const sf::Exception& e)
                {
                    CDebug::error("Failed to create resource, exception: ", e.what());
                    return nullptr;
                }
            }
            
            return dataMap[id].get();
        }

        template<typename T>
        [[nodiscard]] T* getResource(const std::string& id, const TResourceMap<T>& dataMap) const
        {
            if (!dataMap.contains(id)) return nullptr;

            return dataMap.at(id).get();
        }
        
        TResourceMap<sf::Texture> m_textures;
        TResourceMap<sf::SoundBuffer> m_sounds;
        TResourceMap<sf::Font> m_fonts;
    };
}

#endif // TAILS_RESOURCEMANAGER_HPP
