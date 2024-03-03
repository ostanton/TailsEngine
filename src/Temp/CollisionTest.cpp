#include "TailsEngine/Temp/CollisionTest.h"

#include <SFML/Graphics/Sprite.hpp>

#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

void tails::CollisionTest::spawn()
{
    Entity::spawn();

    createComponent<sf::Sprite>()->setTexture(getLevelAssetCache()["tails"].getAssetData<sf::Texture>());
}
