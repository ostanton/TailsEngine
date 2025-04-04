#ifndef EXAMPLE_PLAYER_HPP
#define EXAMPLE_PLAYER_HPP

#include <Tails/Game/Actor.hpp>
#include <Tails/Input/ActionHandle.hpp>

namespace tails
{
    class CSpriteComponent;
    struct SAction;
    struct SActionValue;
}

class CPlayer final : public tails::CActor
{
public:
    CPlayer();

    void shoot();

private:
    void onTick(float deltaSeconds) override;
    void onOverlap(CActor* otherActor) override;
    
    void handleMoveDown(tails::SActionValue actionValue);
    void handleMoveRight(tails::SActionValue actionValue);
    void handleStartSprint(tails::SActionValue actionValue);
    void handleStopSprint(tails::SActionValue actionValue);
    void handleStartShooting(tails::SActionValue actionValue);
    void handleStopShooting(tails::SActionValue actionValue);
    
    tails::CSpriteComponent* m_spriteComponent;
    tails::SActionHandle m_moveDownAction;
    tails::SActionHandle m_moveRightAction;
    tails::SActionHandle m_sprintAction;
    tails::SActionHandle m_shootAction;

    float m_currentSpeed;
    float m_sprintSpeed {500.f};
    float m_walkSpeed {250.f};

    bool m_wishShoot {false};
    float m_shootTimer {0.f};
    float m_fireRate {0.1f};
};

#endif // EXAMPLE_PLAYER_HPP
