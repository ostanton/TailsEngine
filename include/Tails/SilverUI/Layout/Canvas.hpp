#ifndef TAILS_CANVAS_PANEL_HPP
#define TAILS_CANVAS_PANEL_HPP

#include <Tails/Core.hpp>
#include <Tails/SilverUI/Panel.hpp>

namespace tails
{
    class TAILS_API SCanvas final : public SPanel
    {
    public:
        class TAILS_API CCanvasSlot final : public ISlot
        {
        public:
            using ISlot::ISlot;

        private:
            void layout() override;
        };

    private:
        std::unique_ptr<ISlot> makeSlot(std::shared_ptr<SWidget> content) override;
    };
}

#endif // TAILS_CANVAS_PANEL_HPP
