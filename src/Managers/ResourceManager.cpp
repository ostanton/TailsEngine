#include "TailsEngine/Managers/ResourceManager.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

tails::ResourceManager::ResourceManager()
{
    
}

tails::ResourceManager::~ResourceManager()
{
    
}

void tails::ResourceManager::loadTexture(const std::string& id, const std::string& path)
{
    const auto texture {new sf::Texture};

    if (!texture->loadFromFile(path))
    {
        Debug::log("ResourceManager::loadTexture - Failed to load texture from file path");
        return;
    }

    textureManager.addAsset(id, texture);
}

void tails::ResourceManager::loadFont(const std::string& id, const std::string& path)
{
    const auto font {new sf::Font};

    if (!font->loadFromFile(path))
    {
        Debug::log("ResourceManager::loadFont - Failed to load font from file path");
        return;
    }

    fontManager.addAsset(id, font);
}

void tails::ResourceManager::loadSound(const std::string& id, const std::string& path)
{
    const auto buffer {new sf::SoundBuffer};

    if (!buffer->loadFromFile(path))
    {
        Debug::log("ResourceManager::loadSound - Failed to load sound from file path");
        return;
    }

    soundManager.addAsset(id, buffer);
}

sf::Music& tails::ResourceManager::loadMusic(const std::string& path)
{
    if (!music.openFromFile(path))
    {
        Debug::log("ResourceManager::loadMusic - Failed to load music from file path");
    }

    return music;
}

void tails::ResourceManager::loadAndPlayMusic(const std::string& path, bool loop)
{
    loadMusic(path);
    music.play();
    music.setLoop(loop);
}
