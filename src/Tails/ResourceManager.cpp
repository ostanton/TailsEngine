#include <Tails/ResourceManager.hpp>
#include <Tails/Directories.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tails
{
    CResourceManager::CResourceManager() = default;
    CResourceManager::~CResourceManager() = default;

    sf::Texture* CResourceManager::createTexture(const std::string_view id, const std::filesystem::path& filename)
    {
        auto dir = CDirectories::getDirectory("textures");
        return createResource<sf::Texture>(id, dir.append(filename.c_str()));
    }

    sf::Texture* CResourceManager::getTexture(const std::string_view id) const
    {
        return getResource<sf::Texture>(id);
    }

    sf::SoundBuffer* CResourceManager::createSound(const std::string_view id, const std::filesystem::path& filename)
    {
        auto dir = CDirectories::getDirectory("sounds");
        return createResource<sf::SoundBuffer>(id, dir.append(filename.c_str()));
    }

    sf::SoundBuffer* CResourceManager::getSound(const std::string_view id) const
    {
        return getResource<sf::SoundBuffer>(id);
    }

    sf::Font* CResourceManager::createFont(const std::string_view id, const std::filesystem::path& filename)
    {
        auto dir = CDirectories::getDirectory("fonts");
        return createResource<sf::Font>(id, dir.append(filename.c_str()));
    }

    sf::Font* CResourceManager::getFont(std::string_view id) const
    {
        return getResource<sf::Font>(id);
    }
}
