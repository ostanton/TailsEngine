#include "TailsEngine/Temp/TailsEntity.h"

#include <iostream>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "TailsEngine/Core/Viewport.h"
#include "TailsEngine/Core/World.h"
#include "TailsEngine/Core/Components/AnimatedSpriteComponent.h"
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
    
    m_animatedSpriteComponent = createComponent<AnimatedSpriteComponent>();
    m_animatedSpriteComponent->getSprite().setScale(2.f, 2.f);

    m_animatedSpriteComponent->getAnimationPlayer().addAnimation(
        "pointer",
        &getLevelAssetCache()["pointer"].getAssetData<sf::Texture>(),
        sf::Vector2i(33, 33), true);
    m_animatedSpriteComponent->getAnimationPlayer().addAnimation(
        "tails_running",
        &getLevelAssetCache()["tails_running"].getAssetData<sf::Texture>(),
        sf::Vector2i(45, 41), true);

    m_animatedSpriteComponent->getAnimationPlayer().playAnimation("pointer");

    // setting global origin for this entity
    setOrigin(32.f, 32.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getLevelMusicManager().loadAndPlayMusic("Assets/Music/TailsLab.ogg");
    getLevelMusicManager().getMusic().setVolume(50.f);

    m_testScreen = getViewport().createAndDisplayScreen<Screen>();
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
        m_animatedSpriteComponent->getAnimationPlayer().setPlayRate(4.f);
    }
    if (getInputManager().onActionRelease("b"))
    {
        currentSpeed = baseSpeed * walkSpeedMultiplier;
        m_animatedSpriteComponent->getAnimationPlayer().setPlayRate(1.f);
    }

    if (getInputManager().onActionPress("a"))
        m_animatedSpriteComponent->getAnimationPlayer().playAnimation("tails_running");
    if (getInputManager().onActionRelease("a"))
        m_animatedSpriteComponent->getAnimationPlayer().playAnimation("pointer");

    if (getInputManager().onActionPress("l"))
        destroy();

    if (getInputManager().onActionPress("r"))
        getWorld().createAndOpenLevel<Level>();

    if (getInputManager().isActionDown("start"))
        m_testScreen->move(getGlobalDeltaTime() * 50.f, 0.f);
    if (getInputManager().isActionDown("select"))
        m_testScreen->move(getGlobalDeltaTime() * -50.f, 0.f);
}

void tails::TailsEntity::despawn()
{
    Entity::despawn();

    getLevelMusicManager().stop();
    getViewport().destroyScreen(m_testScreen);
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Entity::onStartCollision(otherEntity, otherBounds);

    otherEntity->destroy();
}
