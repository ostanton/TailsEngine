#ifndef TAILS_SOUNDRESOURCE_HPP
#define TAILS_SOUNDRESOURCE_HPP

#include <Tails/Assets/Resource.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace tails
{
    // can be extended for more cool audio functionality, maybe effects and such
    class Sound : public Resource, public sf::SoundBuffer
    {
    protected:
        bool load(const std::string& path) override
        {
            return loadFromFile(path);
        }
    };
}

#endif // TAILS_SOUNDRESOURCE_HPP
