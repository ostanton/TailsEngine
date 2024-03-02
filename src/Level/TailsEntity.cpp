#include "TailsEngine/Level/TailsEntity.h"

#include <SFML/Audio/Music.hpp>

#include "TailsEngine/Core/World.h"
#include "TailsEngine/Managers/InputManager.h"
#include "TailsEngine/Managers/ResourceManager.h"
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
    
    //setTexture(getResourceManager().textureManager.getAssetRef("tails"));
    setOrigin(32.f, 32.f);
    setPosition(480.f, 320.f);

    currentSpeed = baseSpeed * walkSpeedMultiplier;

    getLevelMusicManager().loadAndPlayMusic("Assets/Music/TailsLab.ogg");
    getLevelMusicManager().getMusic().setVolume(50.f);

    // Load a sound for use on user input
    getLevelAssetCache().loadSound("audio_jungle", "Assets/Sounds/AudioJungle.ogg");
    sound.setBuffer(getLevelAssetCache()["audio_jungle"].getAssetData<sf::SoundBuffer>());
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

    if (getInputManager().onActionPress("a"))
        sound.play();

    /**
     * TODO
     * After destroying this entity, the update continues, so it reaches the next getInputManager, and because this
     * entity should be destroyed, it has no outer, so it fails and crashes. I THINK
     *
     * It crashes when there is more than one entity alive. It works fine with only 1 entity
     */

    // This used to work even with multiple entities. Now only works with one!
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

    getLevelMusicManager().stop();
}

void tails::TailsEntity::onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds)
{
    Entity::onStartCollision(otherEntity, otherBounds);

    otherEntity->destroy();
}
