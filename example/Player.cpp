#include "Player.hpp"
#include "Bullet.hpp"

#include <Tails/Game/Components/SpriteComponent.hpp>
#include <Tails/Input/InputSubsystem.hpp>
#include <Tails/Application.hpp>
#include <Tails/Debug.hpp>

CPlayer::CPlayer()
{
    m_spriteComponent = createComponent<tails::CSpriteComponent>();
    m_spriteComponent->setSize({32.f, 32.f});
    m_spriteComponent->setColour(tails::SColour::green);
    setRootComponent(m_spriteComponent);

    m_currentSpeed = m_walkSpeed;

    m_moveDownAction = tails::input::addAction({
        "MoveDown",
        {
            tails::EKeys::Down,
            {tails::EKeys::Up, -1.f},
            tails::EKeys::GamepadLeftStickY,
            tails::EKeys::GamepadDPadDown,
            {tails::EKeys::GamepadDPadUp, -1.f}
        }
    });
    m_moveRightAction = tails::input::addAction({
        "MoveRight",
        {
            tails::EKeys::Right,
            {tails::EKeys::Left, -1.f},
            tails::EKeys::GamepadLeftStickX,
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
        tails::EActionTrigger::Held,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleMoveDown)
    );
    m_moveRightAction.getAction()->bind(
        tails::EActionTrigger::Held,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleMoveRight)
    );
    m_sprintAction.getAction()->bind(
        tails::EActionTrigger::Pressed,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStartSprint)
    );
    m_sprintAction.getAction()->bind(
        tails::EActionTrigger::Released,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStopSprint)
    );
    m_shootAction.getAction()->bind(
        tails::EActionTrigger::Pressed,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStartShooting)
    );
    m_shootAction.getAction()->bind(
        tails::EActionTrigger::Released,
        tails::SOnActionBinding::Delegate::createRaw(this, &CPlayer::handleStopShooting)
    );
}

void CPlayer::shoot()
{
    TAILS_DEBUG_PRINT("SHOOT!\n", 2.f);
    auto const bullet = getLevel()->spawnActor<CBullet>({
        m_spriteComponent->getCentre(),
        getRotation(),
        getScale()
    });
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

void CPlayer::handleMoveDown(const tails::SActionValue actionValue)
{
    move({
        0.f,
        actionValue.get<float>() * m_currentSpeed * tails::IApplication::get().getDeltaSeconds()
    });
}

void CPlayer::handleMoveRight(const tails::SActionValue actionValue)
{
    move({
        actionValue.get<float>() * m_currentSpeed * tails::IApplication::get().getDeltaSeconds(),
        0.f
    });
}

void CPlayer::handleStartSprint(tails::SActionValue actionValue)
{
    m_currentSpeed = m_sprintSpeed;
}

void CPlayer::handleStopSprint(tails::SActionValue actionValue)
{
    m_currentSpeed = m_walkSpeed;
}

void CPlayer::handleStartShooting(tails::SActionValue actionValue)
{
    m_wishShoot = true;
}

void CPlayer::handleStopShooting(tails::SActionValue actionValue)
{
    m_wishShoot = false;
}
