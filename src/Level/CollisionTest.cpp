#include "TailsEngine/Level/CollisionTest.h"

#include "TailsEngine/Managers/ResourceManager.h"

void tails::CollisionTest::spawn()
{
    Entity::spawn();

    setTexture(getResourceManager().textureManager.getAssetRef("tails"));
}
