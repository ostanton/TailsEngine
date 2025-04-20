#ifndef TAILS_SPRITE_COMPONENT_HPP
#define TAILS_SPRITE_COMPONENT_HPP

#include <Tails/Core.hpp>
#include <Tails/World/Components/PrimitiveComponent.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/Rect.hpp>

#include <memory>

namespace tails
{
    class CTexture;
    
    class TAILS_API CSpriteComponent : public CPrimitiveComponent
    {
    public:
        [[nodiscard]] SVector2f getCentre() const noexcept;
        [[nodiscard]] SFloatRect getGlobalBounds() const noexcept override;

        SVector2f size;
        SColour colour;
        std::shared_ptr<CTexture> texture;
        bool useTextureSize {false};

    protected:
        void onRender(CRenderer& renderer) const override;
    };
}

#endif // TAILS_SPRITE_COMPONENT_HPP
