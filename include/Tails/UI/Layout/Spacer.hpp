#ifndef TAILS_SPACER_WIDGET_HPP
#define TAILS_SPACER_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/LeafWidget.hpp>
#include <Tails/Maths/Colour.hpp>

namespace tails::ui
{
    class TAILS_API CSpacer final : public CLeafWidget
    {
    public:
        [[nodiscard]] SVector2f getDesiredSize() const noexcept override;
        void onPaint(const SLayoutData& myLayout, const IRenderer& renderer, float deltaSeconds) const override;

        SVector2f desiredSize;
        SColour debugColour {SColour::transparent};
    };
}

#endif // TAILS_SPACER_WIDGET_HPP
