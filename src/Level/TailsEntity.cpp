#include "TailsEngine/Level/TailsEntity.h"

#include <iostream>
#include <SFML/Audio/Music.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Debug/Debug.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/Assets/AssetCache.h"
#include "TailsEngine/Managers/Assets/AssetInfo.h"

tails::TailsEntity::TailsEntity()
{
    currentSpeed = baseSpeed * walkSpeedMultiplier;
}

void tails::TailsEntity::spawn()
{
    Entity::spawn();
    
    setTexture(getLevelAssetCache()["tails"].getAssetData<sf::Texture>());
    
    setOrigin(32.f, 32.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getLevelMusicManager().loadAndPlayMusic("Assets/Music/TailsLab.ogg");
    getLevelMusicManager().getMusic().setVolume(50.f);
}

void tails::TailsEntity::update(float deltaTime)
{
    Entity::update(deltaTime);

    rotate(deltaTime * 25.f);

    if (timer < 2.f)
    {
        timer += deltaTime;
    }
    else
    {
        if (!setOtherMusic)
        {
            setOtherMusic = true;
            // play some other music
            getLevelMusicManager().loadAndPlayMusic("Assets/Music/EmeraldCity.ogg");
        }
    }
}

void tails::TailsEntity::processInput(sf::Event& e)
{
    Entity::processInput(e);

    if (getInputManager().isActionDown("up"))
        move(0.f, getGlobalDeltaTime() * -currentSpeed);
    if (getInputManager().isActionDown("down"))
        move(0.f, getGlobalDeltaTime() * currentSpeed);
    if (getInputManager().isActionDown("left"))
        move(getGlobalDeltaTime() * -currentSpeed, 0.f);
    if (getInputManager().isActionDown("right"))
        move(getGlobalDeltaTime() * currentSpeed, 0.f);

    if (getInputManager().onActionPress("b"))
        currentSpeed = baseSpeed * runSpeedMultiplier;
    if (getInputManager().onActionRelease("b"))
        currentSpeed = baseSpeed * walkSpeedMultiplier;

    /** TODO
     * Without a return, processInput() finishes executing, failing to get InputManager because this object is
     * technically destroyed. How to fix? Maybe buffer destruction until after this has finished? Not sure
     */

    if (getInputManager().onActionPress("l"))
    {
        destroy();
        return;
    }

    if (getInputManager().onActionPress("r"))
        getWorld()->createAndOpenLevel<Level>();
}

void tails::TailsEntity::despawn()
{
    Entity::despawn();

    getLevelMusicManager().stop();
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Entity::onStartCollision(otherEntity, otherBounds);

    /** TODO
     * Temporarily commented out as it causes a crash with onCollision in base Entity where it prints the class name
     * but the entity it gets the class name from is not fully valid
     */
    //otherEntity->destroy();
}
