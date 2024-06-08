#ifndef TAILS_TEXTURERESOURCE_HPP
#define TAILS_TEXTURERESOURCE_HPP

#include <Tails/Assets/Resource.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace tails
{
    class Texture : public Resource, public sf::Texture
    {
    protected:
        bool load(const std::string& path) override
        {
            return loadFromFile(path);
        }
    };
}

#endif // TAILS_TEXTURERESOURCE_HPP
