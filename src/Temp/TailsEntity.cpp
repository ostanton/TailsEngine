#include "TailsEngine/Temp/TailsEntity.h"

#include <iostream>
#include <SFML/Audio/Music.hpp>

#include "TailsEngine/Core/InputTypes.h"
#include "TailsEngine/Core/Viewport.h"
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
    
    m_animatedSprite = createSprite(getLevelAssetCache()["tails_running"].getAssetData<sf::Texture>());
    m_animatedSprite->getAnimationPlayer().addAnimation("tails_running", sf::Vector2i(45, 41), 8);
    m_animatedSprite->getAnimationPlayer().playAnimation("tails_running");

    createHitBox();
    drawHitBoxes(true);

    // setting global origin for this entity
    setOrigin(32.f, 32.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getLevelMusicManager().loadAndPlayMusic("Assets/Music/TailsLab.ogg");
    getLevelMusicManager().getMusic().setVolume(50.f);
}

void tails::TailsEntity::update(float deltaTime)
{
    Entity::update(deltaTime);

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

    setViewCameraPosition(getPosition());
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
    {
        currentSpeed = baseSpeed * runSpeedMultiplier;
        m_animatedSprite->getAnimationPlayer().setPlayRate(4.f);
    }
    if (getInputManager().onActionRelease("b"))
    {
        currentSpeed = baseSpeed * walkSpeedMultiplier;
        m_animatedSprite->getAnimationPlayer().setPlayRate(1.f);
    }

    if (getInputManager().onActionPress("l"))
        destroy();

    if (getInputManager().onActionPress("r"))
        getWorld().createAndOpenLevel<Level>();

    if (getInputManager().onActionPress("start"))
    {
        setInputMode(InputMode::Viewport);
        m_testScreen = getViewport().createAndDisplayScreen<Screen>();
        pauseGame(true);
    }
}

void tails::TailsEntity::despawn()
{
    Entity::despawn();

    getLevelMusicManager().stop();
    getViewport().destroyScreen(m_testScreen);
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity)
{
    Entity::onStartCollision(otherEntity);

    otherEntity->destroy();
}
