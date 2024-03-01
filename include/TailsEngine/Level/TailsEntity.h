#pragma once
#include <SFML/Audio/Sound.hpp>

#include "Entity.h"

namespace tails
{
/**
 * \brief A simple example class displaying a texture in the sprite that we are deriving, using the
 * resource manager class to load and contain a texture of Tails
 */
class TailsEntity : public Entity
{
public:
    void spawn() override;
    void update(float deltaTime) override;
    void processInput(sf::Event& e) override;
    void despawn() override;

    void onStartCollision(Entity* otherEntity, const sf::FloatRect& otherBounds) override;

    float walkSpeedMultiplier {1.f};
    float runSpeedMultiplier{3.f};
    float baseSpeed {200.f};
    float currentSpeed;

    float timer {0.f};
    bool setOtherMusic {false};

    sf::Sound sound;
};

}
