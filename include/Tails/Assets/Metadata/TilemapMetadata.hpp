#ifndef TAILS_TILEMAPMETADATA_HPP
#define TAILS_TILEMAPMETADATA_HPP

#include <Tails/Config.hpp>
#include <Tails/Assets/Metadata/SpriteMetadata.hpp>

#include <SFML/System/Vector2.hpp>

namespace tails
{
    struct TAILS_API TilemapMetadata : SpriteMetadata
    {
        sf::Vector2u tileSize;
    };
}

#endif //TAILS_TILEMAPMETADATA_HPP
