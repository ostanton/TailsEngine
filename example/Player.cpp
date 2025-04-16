#include "Player.hpp"
#include "Bullet.hpp"

#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/World/Level.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Application.hpp>
#include <Tails/Debug.hpp>
#include <Tails/World/ActorRegistry.hpp>

TAILS_REGISTER_ACTOR(CPlayer, "Player")

CPlayer::CPlayer()
{
    m_spriteComponent = createComponent<tails::CSpriteComponent>();
    m_spriteComponent->size = {16.f, 16.f};
    m_spriteComponent->colour = tails::SColour::green;
    m_spriteComponent->texture = m_sprite.load();
    setRootComponent(m_spriteComponent);

    m_currentSpeed = m_walkSpeed;

    m_moveDownAction = tails::input::addAction({
        "MoveDown",
        {
            tails::EKeys::Down,
            {tails::EKeys::Up, -1.f},
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
    TAILS_DEBUG_PRINT(2.f, "SHOOT!");
    auto const bullet = getLevel()->spawnActor<CBullet>({
        m_spriteComponent->getCentre(),
        getRotation(),
        getScale()
    }, -10);
    bullet->moveDirection = {1.f, 0.f};
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
}

void CPlayer::onOverlap(CActor* otherActor)
{
    CActor::onOverlap(otherActor);

    if (otherActor)
        std::cout << "Overlapping " << otherActor << '\n';
    else
        std::cout << "Overlapping INVALID actor!\n";
}

void CPlayer::handleMoveDown(const tails::input::SActionValue actionValue)
{
    move({
        0.f,
        actionValue.get<float>() * m_currentSpeed * tails::getDeltaSeconds()
    });
}

void CPlayer::handleMoveRight(const tails::input::SActionValue actionValue)
{
    move({
        actionValue.get<float>() * m_currentSpeed * tails::getDeltaSeconds(),
        0.f
    });
}

void CPlayer::handleStartSprint(const tails::input::SActionValue actionValue)
{
    m_currentSpeed = m_sprintSpeed;
    m_spriteComponent->visible = !m_spriteComponent->visible;
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
