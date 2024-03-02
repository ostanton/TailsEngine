#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace tails
{
struct AssetInfo;
/**
 * \brief The asset cache that holds all the assets in use in a given context. This is where assets are
 * loaded and unloaded for that context.
 *
 * Contexts can include:
 * - Level
 * - World
 * - Global
 * - Viewport
 * - Screen
 */
class AssetCache
{
public:
    /*
     * Attempt to make a non-type specific load method. Compiler does not like assigning non-typename objects to
     * typename objects, like assigning the sound (sf::SoundBuffer) variable to newAsset when newAsset's T is of
     * sf::Texture type. SoundBuffer and Texture are incompatible. Fix? Separate methods or something for each asset
    template<typename T>
    bool loadAsset(const std::string& id, const std::string& path)
    {
        if (m_assets.contains(id))
        {
            Debug::log("AssetCache::loadAsset - An asset with that ID is already loaded");
            return false;
        }
        
        T* newAsset { new T };
        auto assetType {AssetType::None};

        if (typeid(T) == typeid(sf::Texture))
        {
            const auto texture {new sf::Texture};
            if (!texture->loadFromFile(path))
            {
                Debug::log("AssetCache::loadAsset - Failed to load asset from path");
                delete newAsset;
                delete texture;
                return false;
            }

            assetType = AssetType::Texture;
            newAsset = texture;
        }
        
        else if (typeid(T) == typeid(sf::SoundBuffer))
        {
            auto sound {new sf::SoundBuffer};
            if (!sound->loadFromFile(path))
            {
                Debug::log("AssetCache::loadAsset - Failed to load asset from path");
                delete newAsset;
                delete sound;
                return false;
            }

            assetType = AssetType::Sound;
            newAsset = sound;
        }
        
        else if (typeid(T) == typeid(sf::Font))
        {
            auto font {new sf::Font};
            if (!font->loadFromFile(path))
            {
                Debug::log("AssetCache::loadAsset - Failed to load asset from path");
                delete newAsset;
                delete font;
                return false;
            }

            assetType = AssetType::Font;
            newAsset = font;
        }

        std::unique_ptr<AssetInfo> assetInfo {new AssetInfo(assetType, AssetState::Loaded, path)};
        assetInfo->m_data = newAsset;
        m_assets.emplace(id, std::move(assetInfo));
        return true;
    }
    */

    /*
     * Could have a loadAsset<T>() which just selects one of the following functions based on the typeid of T,
     * but that would then require including sf::Texture, etc. in this header, which I'm not a fan of
     */
    
    bool loadTexture(const std::string& id, const std::string& path);
    bool loadSound(const std::string& id, const std::string& path);
    bool loadFont(const std::string& id, const std::string& path);

    AssetInfo& getAssetInfo(const std::string& id) const;

    AssetInfo& operator[](const std::string& id) const;

private:
    std::unordered_map<std::string, std::unique_ptr<AssetInfo>> m_assets;
};

}
