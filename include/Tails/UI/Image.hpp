#ifndef TAILS_IMAGE_WIDGET_HPP
#define TAILS_IMAGE_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/LeafWidget.hpp>
#include <Tails/Maths/Colour.hpp>

#include <memory>

namespace tails
{
    class CTexture;
}

namespace tails::ui
{
    class TAILS_API CImage final : public CLeafWidget
    {
    public:
        [[nodiscard]] SVector2f getDesiredSize() const noexcept override;
        void onPaint(const SLayoutData& myLayout, float deltaSeconds) const override;

        std::shared_ptr<CTexture> texture;
        SVector2f customSize {32.f, 32.f};
        /** When false, use the texture's size (if valid), otherwise use customSize */
        bool useCustomSize {false};
        SColour tint {SColour::white};
    };
}

#endif // TAILS_IMAGE_WIDGET_HPP
