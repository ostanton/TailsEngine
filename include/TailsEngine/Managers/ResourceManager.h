#pragma once

#include <SFML/Audio/Music.hpp>

#include "AssetManager.h"

namespace sf
{
class Sound;
class Texture;
class Font;
class SoundBuffer;
class Music;
}

namespace tails
{
/**
 * \brief A simple global resource manager for assets to all be in one place instead of loaded about everywhere.
 * Should replace with a more generic manager later, with void* as a type or something.
 *
 * To load an asset, call one of the designated "load*" methods. To get an asset to use it, call "getAsset" from
 * the designated asset manager member. For example, to load a texture, call "loadTexture". Then to use that
 * texture in the game for a sprite or something, do ResourceManager.textureManager.getAsset(id)
 */
class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();
    
    /* TEXTURES */
    
    /**
     * \brief Loads a texture from file for use
     * \param id New identifier for this texture
     * \param path System path to the texture file
     */
    void loadTexture(const std::string& id, const std::string& path);

    /* FONTS */

    /**
     * \brief Loads a font from file for use
     * \param id New identifier for this font
     * \param path System path to the font file
     */
    void loadFont(const std::string& id, const std::string& path);

    /* SOUNDS */

    /**
     * \brief Loads a sound from file for use
     * \param id New identifier for this sound
     * \param path System path to the sound file
     */
    void loadSound(const std::string& id, const std::string& path);

    // How would we manage the sounds currently being played? Pointers?
    // If pointers, how do we delete them after it's finished playing?
    // void playSound(const std::string& id);

    /**
     * \brief Loads a music file and opens it in the music member
     * \param path System path to the music file
     * \return Reference to the music object
     */
    sf::Music& loadMusic(const std::string& path);

    /**
     * \brief Loads and plays a music file, optionally looping
     * \param path System path to the music file
     * \param loop Should the music loop when it reaches the end
     */
    void loadAndPlayMusic(const std::string& path, bool loop = true);
    
    AssetManager<sf::Texture> textureManager;
    AssetManager<sf::Font> fontManager;
    AssetManager<sf::SoundBuffer> soundManager;
    /**
     * \brief Only one global music can be playing at one time (can have numerous local ones). Setting volume,
     * etc. on this object serves as a global music volume.
     */
    sf::Music music;
};

}
