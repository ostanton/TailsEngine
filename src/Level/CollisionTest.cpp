#include "TailsEngine/Level/CollisionTest.h"

#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

void tails::CollisionTest::spawn()
{
    Entity::spawn();

    setTexture(getLevelAssetCache()["tails"].getAssetData<sf::Texture>());
}
