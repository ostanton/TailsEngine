#ifndef EXAMPLE_PLAYER_HPP
#define EXAMPLE_PLAYER_HPP

#include <Tails/World/Actor.hpp>
#include <Tails/Input/ActionHandle.hpp>
#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Texture.hpp>

namespace tails
{
    class CCameraComponent;
    
    namespace input
    {
        struct SAction;
        struct SActionValue;
    }
}

class CPlayer final : public tails::CActor
{
public:
    CPlayer();

    void shoot();

private:
    void onSpawn() override;
    void onTick(float deltaSeconds) override;
    void onOverlap(CActor* otherActor) override;
    
    void handleMoveDown(tails::input::SActionValue actionValue);
    void handleMoveRight(tails::input::SActionValue actionValue);
    void handleStartSprint(tails::input::SActionValue actionValue);
    void handleStopSprint(tails::input::SActionValue actionValue);
    void handleStartShooting(tails::input::SActionValue actionValue);
    void handleStopShooting(tails::input::SActionValue actionValue);

    tails::CCameraComponent* m_cameraComponent;
    tails::input::SActionHandle m_moveDownAction;
    tails::input::SActionHandle m_moveRightAction;
    tails::input::SActionHandle m_sprintAction;
    tails::input::SActionHandle m_shootAction;

    float m_currentSpeed;
    float m_sprintSpeed {500.f};
    float m_walkSpeed {1.f};

    bool m_wishShoot {false};
    float m_shootTimer {0.f};
    float m_fireRate {0.1f};

    float m_zoomTimer {0.f};

    tails::TAssetPtr<tails::CTexture> m_sprite {"face.png"};
};

#endif // EXAMPLE_PLAYER_HPP
