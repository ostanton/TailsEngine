#include "TailsEngine/Level/CollisionTest.h"

#include "TailsEngine/Managers/ResourceManager.h"

void tails::CollisionTest::spawn()
{
    Entity::spawn();

    setTexture(getResourceManager().textureManager.getAssetRef("tails"));
    setPosition(400.f, 400.f);
}
