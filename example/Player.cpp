#include "Player.hpp"
#include "Bullet.hpp"

#include <Tails/World/Components/AnimatedSpriteComponent.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Application.hpp>
#include <Tails/Debug.hpp>
#include <Tails/World/ActorRegistry.hpp>
#include <Tails/World/Components/CameraComponent.hpp>
#include <Tails/World/Components/ShapeComponent.hpp>
#include <Tails/Renderer/Shapes.hpp>

#include <iostream>

TAILS_REGISTER_ACTOR(CPlayer, "Player")

CPlayer::CPlayer()
{
    auto const spriteComponent = createComponent<tails::CSpriteComponent>();
    //spriteComponent->texture = m_sprite.load();
    spriteComponent->size = {64.f, 64.f};
    spriteComponent->useTextureSize = false;
    spriteComponent->colour = tails::SColour::red;
    spriteComponent->transform.setOrigin({0.5f});
    setRootComponent(spriteComponent);

    m_cameraComponent = createComponent<tails::CCameraComponent>();
    m_cameraComponent->setParent(spriteComponent);

    auto const testSprite = createComponent<tails::CSpriteComponent>();
    testSprite->setParent(spriteComponent);
    testSprite->size = {32.f, 32.f};
    testSprite->transform.setPosition({32.f, 32.f});
    testSprite->colour = tails::SColour::green;

    auto const shapeComp = createComponent<tails::CShapeComponent>();
    shapeComp->setParent(spriteComponent);
    shapeComp->transform.setPosition({0.f, 64.f});
    shapeComp->vertices = tails::shapes::circle(32.f, 16, tails::SFloatColour::green);

    m_currentSpeed = m_walkSpeed;

    m_moveDownAction = tails::input::addAction({
        "MoveDown",
        {
            {tails::EKeys::Down, -1.f},
            tails::EKeys::Up,
            {tails::EKeys::GamepadLeftStickY, 1.f, 0.2f},
            tails::EKeys::GamepadDPadDown,
            {tails::EKeys::GamepadDPadUp, -1.f}
        }
    });
    m_moveRightAction = tails::input::addAction({
        "MoveRight",
        {
            tails::EKeys::Right,
            {tails::EKeys::Left, -1.f},
            {tails::EKeys::GamepadLeftStickX, 1.f, 0.2f},
            tails::EKeys::GamepadDPadRight,
            {tails::EKeys::GamepadDPadLeft, -1.f}
        }
    });
    m_sprintAction = tails::input::addAction({
        "Sprint",
        {
            tails::EKeys::Z,
            tails::EKeys::GamepadFaceBottom
        }
    });
    m_shootAction = tails::input::addAction({
        "Shoot",
        {
            tails::EKeys::X,
            tails::EKeys::GamepadFaceLeft
        }
    });

    m_moveDownAction.getAction()->bind(
        tails::input::EActionTrigger::Held,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleMoveDown)
    );
    m_moveRightAction.getAction()->bind(
        tails::input::EActionTrigger::Held,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleMoveRight)
    );
    m_sprintAction.getAction()->bind(
        tails::input::EActionTrigger::Pressed,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStartSprint)
    );
    m_sprintAction.getAction()->bind(
        tails::input::EActionTrigger::Released,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStopSprint)
    );
    m_shootAction.getAction()->bind(
        tails::input::EActionTrigger::Pressed,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStartShooting)
    );
    m_shootAction.getAction()->bind(
        tails::input::EActionTrigger::Released,
        tails::input::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStopShooting)
    );
}

void CPlayer::shoot()
{
    TAILS_DEBUG_PRINT(2.f, TAILS_FMT("SHOOT {}!", 1.f));
    //TAILS_DEBUG_PRINTF(2.f, "Hello! {}", 2);
    auto const bullet = getLevel()->spawnActor<CBullet>(getTransform(), -10);
    bullet->moveDirection = {1.f, 0.f};
    //m_cameraComponent->transform.rotate(tails::SFloatAngle::degrees(1.f));
    //m_cameraComponent->camera.zoom += 0.1f;
    scale({1.01f});
}

void CPlayer::onSpawn()
{
    CActor::onSpawn();

    getLevel()->setActiveCamera(m_cameraComponent);
}

void CPlayer::onTick(const float deltaSeconds)
{
    CActor::onTick(deltaSeconds);

    m_shootTimer -= deltaSeconds;
    
    if (m_wishShoot && m_shootTimer <= 0.f)
    {
        m_shootTimer = m_fireRate;
        shoot();
    }

    const auto transform = getTransform();
    TAILS_DEBUG_PRINT(0.f, TAILS_FMT("Player pos: {{ {}, {} }}", transform.getPosition().x, transform.getPosition().y));
}

void CPlayer::onStartCollision(CActor* otherActor, tails::CComponent* otherComponent)
{
    CActor::onStartCollision(otherActor, otherComponent);

    TAILS_DEBUG_PRINT(2.f, "Started collision");
}

void CPlayer::onEndCollision(CActor* otherActor, tails::CComponent* otherComponent)
{
    CActor::onEndCollision(otherActor, otherComponent);

    TAILS_DEBUG_PRINT(2.f, "Ended collision");
}

void CPlayer::handleMoveDown(const tails::input::SActionValue actionValue)
{
    move({
        0.f,
        actionValue.get<float>() * m_currentSpeed * tails::app::getCurrentFrameInfo().getDeltaSeconds()
    });
}

void CPlayer::handleMoveRight(const tails::input::SActionValue actionValue)
{
    move({
        actionValue.get<float>() * m_currentSpeed * tails::app::getCurrentFrameInfo().getDeltaSeconds(),
        0.f
    });
}

void CPlayer::handleStartSprint(const tails::input::SActionValue actionValue)
{
    m_currentSpeed = m_sprintSpeed;
    setVisible(!isVisible());
}

void CPlayer::handleStopSprint(const tails::input::SActionValue actionValue)
{
    m_currentSpeed = m_walkSpeed;
}

void CPlayer::handleStartShooting(const tails::input::SActionValue actionValue)
{
    m_wishShoot = true;
}

void CPlayer::handleStopShooting(const tails::input::SActionValue actionValue)
{
    m_wishShoot = false;
}
