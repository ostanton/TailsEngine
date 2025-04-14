#ifndef EXAMPLE_BULLET_HPP
#define EXAMPLE_BULLET_HPP

#include <Tails/World/Actor.hpp>
#include <Tails/World/Components/SpriteComponent.hpp>
#include <Tails/Assets/AssetPtr.hpp>
#include <Tails/Assets/Texture.hpp>

class CBullet final : public tails::CActor
{
public:
    CBullet()
    {
        m_spriteComponent = createComponent<tails::CSpriteComponent>();
        m_spriteComponent->setSize({16.f, 4.f});
        m_spriteComponent->setColour(tails::SColour::yellow);
        m_spriteComponent->setTexture(m_texture.load());
        setRootComponent(m_spriteComponent);
    }

    tails::SVector2f moveDirection;

private:
    void onTick(const float deltaSeconds) override
    {
        move(moveDirection * m_speed * deltaSeconds);

        m_lifeTimer += deltaSeconds;

        // destroy ourselves after a bit
        if (m_lifeTimer >= 0.5f)
            destroy();
    }
    
    tails::CSpriteComponent* m_spriteComponent;

    float m_speed {750.f};
    float m_lifeTimer {0.f};

    tails::TAssetPtr<tails::CTexture> m_texture {"face.png"};
};

#endif // EXAMPLE_BULLET_HPP
