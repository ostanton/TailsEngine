#include "TailsEngine/Level/TailsEntity.h"

#include <SFML/Audio/Music.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/ResourceManager.h"

void tails::TailsEntity::spawn()
{
    Entity::spawn();

    getResourceManager().loadTexture("tails", "Assets/Textures/Tails.png");
    setTexture(getResourceManager().textureManager.getAssetRef("tails"));
    setOrigin(32.f, 32.f);
    setPosition(480.f, 320.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getResourceManager().loadMusic("Assets/Music/TailsLab.ogg");
    getResourceManager().music.setVolume(50.f);
    getResourceManager().music.play();

    // Load a sound for use on user input
    getResourceManager().loadSound("audio_jungle", "Assets/Sounds/AudioJungle.ogg");
    sound.setBuffer(getResourceManager().soundManager.getAssetRef("audio_jungle"));
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
            getResourceManager().loadAndPlayMusic("Assets/Music/EmeraldCity.ogg");
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

    if (getInputManager().onActionPress("a"))
        sound.play();

    /**
     * TODO
     * After destroying this entity, the update continues, so it reaches the next getInputManager, and because this
     * entity should be destroyed, it has no outer, so it fails and crashes. I THINK
     *
     * It crashes when there is more than one entity alive. It works fine with only 1 entity
     */

    // This does not work even if there is only one, because of the aforementioned TODO
    if (getInputManager().onActionPress("l"))
        destroy();

    /**
     * This doesn't work with more than one entity because we are still processing input (the next frame maybe?)
     * on entities that should be destroyed, causing a crash. Only one entity means that's the only one destroyed?
     */
    if (getInputManager().onActionPress("r"))
        getWorld()->createAndOpenLevel<Level>();
}

void tails::TailsEntity::despawn()
{
    Entity::despawn();

    getResourceManager().music.stop();
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Entity::onStartCollision(otherEntity, otherBounds);

    otherEntity->destroy();
}
