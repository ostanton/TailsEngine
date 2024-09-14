#include <Tails/ResourceManager.hpp>
#include <Tails/Directories.hpp>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Graphics/Font.hpp>

namespace tails
{
    CResourceManager::CResourceManager() = default;
    CResourceManager::~CResourceManager() = default;

    sf::Texture* CResourceManager::createTexture(const std::string& id, const std::string& filename)
    {
        return createResource(id, CDirectories::getDirectory("textures") + filename, m_textures);
    }

    sf::Texture* CResourceManager::getTexture(const std::string& id) const
    {
        return getResource(id, m_textures);
    }

    sf::SoundBuffer* CResourceManager::createSound(const std::string& id, const std::string& filename)
    {
        return createResource(id, CDirectories::getDirectory("sounds") + filename, m_sounds);
    }

    sf::SoundBuffer* CResourceManager::getSound(const std::string& id) const
    {
        return getResource(id, m_sounds);
    }

    sf::Font* CResourceManager::createFont(const std::string& id, const std::string& filename)
    {
        return createResource(id, CDirectories::getDirectory("fonts") + filename, m_fonts);
    }

    sf::Font* CResourceManager::getFont(const std::string& id) const
    {
        return getResource(id, m_fonts);
    }
}
