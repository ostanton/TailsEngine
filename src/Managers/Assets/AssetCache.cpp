#include "TailsEngine/Managers/Assets/AssetCache.h"

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

tails::AssetCache::AssetCache()
{
    
}

tails::AssetCache::~AssetCache()
{
    
}

bool tails::AssetCache::loadTexture(const std::string& id, const std::string& path)
{
    auto texture {new sf::Texture};

    if (!texture->loadFromFile(path))
    {
        delete texture;
        return false;
    }

    texture->setSmooth(false);
    
    m_assets.emplace(id, std::make_unique<AssetInfo>(texture, AssetInfo::Texture, AssetInfo::Loaded, path));
    return true;
}

bool tails::AssetCache::loadSound(const std::string& id, const std::string& path)
{
    auto sound {new sf::SoundBuffer};

    if (!sound->loadFromFile(path))
    {
        delete sound;
        return false;
    }

    m_assets.emplace(id, std::make_unique<AssetInfo>(sound, AssetInfo::Sound, AssetInfo::Loaded, path));
    return true;
}

bool tails::AssetCache::loadFont(const std::string& id, const std::string& path)
{
    auto font {new sf::Font};

    if (!font->loadFromFile(path))
    {
        delete font;
        return false;
    }

    font->setSmooth(false);

    m_assets.emplace(id, std::make_unique<AssetInfo>(font, AssetInfo::Font, AssetInfo::Loaded, path));
    return true;
}

bool tails::AssetCache::loadAsset(const std::string& id, const std::string& path)
{
    if (loadTexture(id, path))
        return true;

    if (loadSound(id, path))
        return true;

    if (loadFont(id, path))
        return true;

    return false;
}

bool tails::AssetCache::unloadAsset(const std::string& id)
{
    if (m_assets.contains(id))
    {
        m_assets.erase(id);
        return true;
    }

    return false;
}

tails::AssetInfo& tails::AssetCache::getAssetInfo(const std::string& id) const
{
    if (!m_assets.contains(id))
        Debug::log("AssetCache::getAsset - Failed to find asset via ID");

    return *m_assets.find(id)->second;
}

tails::AssetInfo& tails::AssetCache::operator[](const std::string& id) const
{
    return getAssetInfo(id);
}
