#include "TailsEngine/Level/TailsEntity.h"

#include <SFML/Audio/Music.hpp>

#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/ResourceManager.h"

void tails::TailsEntity::spawn()
{
    Entity::spawn();

    // Use full path because local path don't work for some reason, work out?!
    getResourceManager().loadTexture("tails", "F:/Libraries/TailsEngine/src/Assets/Textures/Tails.png");
    setTexture(getResourceManager().textureManager.getAssetRef("tails"));
    setOrigin(32.f, 32.f);
    setPosition(480.f, 320.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getResourceManager().loadMusic("F:/Libraries/TailsEngine/src/Assets/Music/TailsLab.ogg");
    getResourceManager().music.setVolume(50.f);
    getResourceManager().music.play();

    // Load a sound for use on user input
    getResourceManager().loadSound("audio_jungle", "F:/Libraries/TailsEngine/src/Assets/Sounds/AudioJungle.ogg");
    sound.setBuffer(getResourceManager().soundManager.getAssetRef("audio_jungle"));
}

void tails::TailsEntity::update(float deltaTime)
{
    Entity::update(deltaTime);

    if (getInputManager().isActionDown("up"))
        move(0.f, deltaTime * -currentSpeed);
    if (getInputManager().isActionDown("down"))
        move(0.f, deltaTime * currentSpeed);
    if (getInputManager().isActionDown("left"))
        move(deltaTime * -currentSpeed, 0.f);
    if (getInputManager().isActionDown("right"))
        move(deltaTime * currentSpeed, 0.f);

    if (getInputManager().onActionPress("b"))
        currentSpeed = baseSpeed * runSpeedMultiplier;
    if (getInputManager().onActionRelease("b"))
        currentSpeed = baseSpeed * walkSpeedMultiplier;

    if (getInputManager().onActionPress("a"))
        sound.play();

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
            getResourceManager().loadAndPlayMusic("F:/Libraries/TailsEngine/src/Assets/Music/EmeraldCity.ogg");
        }
    }
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Entity::onStartCollision(otherEntity, otherBounds);

    setColor(sf::Color::Red);
}

void tails::TailsEntity::onEndCollision()
{
    Entity::onEndCollision();

    setColor(sf::Color::White);
}
