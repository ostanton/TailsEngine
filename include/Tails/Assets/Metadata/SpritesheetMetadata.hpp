#ifndef TAILS_SPRITESHEETMETADATA_HPP
#define TAILS_SPRITESHEETMETADATA_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/Metadata/SpriteMetadata.hpp>

#include <SFML/Graphics/Rect.hpp>

#include <vector>
#include <string>
#include <unordered_map>

namespace tails
{
    struct TAILS_API SpritesheetMetadata : SpriteMetadata
    {
        std::unordered_map<std::string, std::vector<sf::IntRect>> animations;
    };
} // tails

#endif //TAILS_SPRITESHEETMETADATA_HPP
