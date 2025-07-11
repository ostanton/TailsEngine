#ifndef TAILS_SPRITE_COMPONENT_HPP
#define TAILS_SPRITE_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/Component.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Colour.hpp>

#include <memory>

namespace tails
{
    class CTexture;
    
    class TAILS_API CSpriteComponent : public CComponent
    {
    public:
        [[nodiscard]] SVector2f getCentre() const noexcept;

        SVector2f size;
        SColour colour;
        std::shared_ptr<CTexture> texture;
        bool useTextureSize {false};

    protected:
        void onTick(float deltaSeconds) override;
        void onRender(CLevelRenderBatch& renderBatch) const override;
    };
}

#endif // TAILS_SPRITE_COMPONENT_HPP
