#pragma once

#include "AssetManager.h"

namespace sf
{
class Texture;
class Font;
class SoundBuffer;
}

namespace tails
{
/**
 * \brief A simple global resource manager for assets to all be in one place instead of loaded about everywhere.
 * Should replace with a more generic manager later, with void* as a type or something.
 *
 * To load an asset, call one of the designated "load_" methods. To get an asset to use it, call "getAsset" from
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
    
    AssetManager<sf::Texture> textureManager;
    AssetManager<sf::Font> fontManager;
    AssetManager<sf::SoundBuffer> soundManager;
};

}
