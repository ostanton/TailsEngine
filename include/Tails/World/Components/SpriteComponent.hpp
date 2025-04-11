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
        void setSize(SVector2f size);
        [[nodiscard]] SVector2f getSize() const;

        [[nodiscard]] SVector2f getCentre() const noexcept;

        void setColour(SColour colour);
        [[nodiscard]] SColour getColour() const;

        void setTexture(std::shared_ptr<CTexture> texture);
        [[nodiscard]] std::shared_ptr<CTexture> getTexture() const;

        [[nodiscard]] SFloatRect getGlobalBounds() const noexcept override;

    protected:
        void onRender(IRenderer& renderer) const override;
        
    private:
        SVector2f m_size;
        SColour m_colour;
        std::shared_ptr<CTexture> m_texture;
    };
}

#endif // TAILS_SPRITE_COMPONENT_HPP
