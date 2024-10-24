#include <Tails/ResourceManager.hpp>
#include <Tails/Directories.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tails
{
    CResourceManager::CResourceManager() = default;
    CResourceManager::~CResourceManager() = default;

    sf::Texture* CResourceManager::createTexture(std::string_view id, const std::filesystem::path& filename)
    {
        return createResource<sf::Texture>(id, CDirectories::getDirectory("textures") + filename.string());
    }

    sf::Texture* CResourceManager::getTexture(std::string_view id) const
    {
        return getResource<sf::Texture>(id);
    }

    sf::SoundBuffer* CResourceManager::createSound(std::string_view id, const std::filesystem::path& filename)
    {
        return createResource<sf::SoundBuffer>(id, CDirectories::getDirectory("sounds") + filename.string());
    }

    sf::SoundBuffer* CResourceManager::getSound(std::string_view id) const
    {
        return getResource<sf::SoundBuffer>(id);
    }

    sf::Font* CResourceManager::createFont(std::string_view id, const std::filesystem::path& filename)
    {
        return createResource<sf::Font>(id, CDirectories::getDirectory("fonts") + filename.string());
    }

    sf::Font* CResourceManager::getFont(std::string_view id) const
    {
        return getResource<sf::Font>(id);
    }
}
