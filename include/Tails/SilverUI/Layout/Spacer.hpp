#ifndef TAILS_SPACER_WIDGET_HPP
#define TAILS_SPACER_WIDGET_HPP

#include <Tails/Core.hpp>
#include <Tails/SilverUI/Widget.hpp>
#include <Tails/Maths/Colour.hpp>

namespace tails
{
    class TAILS_API SSpacer final : public SWidget
    {
    public:
        [[nodiscard]] SVector2f getMinimumSize() const noexcept override;

        SVector2f desiredSize;
        SColour debugColour {SColour::transparent};

    private:
        void onRender(IRenderer& renderer) const override;
    };
}

#endif // TAILS_SPACER_WIDGET_HPP
