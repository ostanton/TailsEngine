#ifndef TAILS_FONTRESOURCE_HPP
#define TAILS_FONTRESOURCE_HPP

#include <Tails/Assets/Resource.hpp>

#include <SFML/Graphics/Font.hpp>

namespace tails
{
    class TAILS_API Font : public Resource, public sf::Font
    {
    protected:
        bool load(const std::string& path) override
        {
            return loadFromFile(path);
        }
    };
}

#endif // TAILS_FONTRESOURCE_HPP
