#include "TailsEngine/Temp/CollisionTest.h"

#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

void tails::CollisionTest::spawn()
{
    Entity::spawn();

    createSprite(getLevelAssetCache()["tails"].getAssetData<sf::Texture>())->isAnimated = false;
    createHitBox();
    drawHitBoxes(true);
}
