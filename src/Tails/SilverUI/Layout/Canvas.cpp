#include <Tails/SilverUI/Layout/Canvas.hpp>

namespace tails
{
    void SCanvas::CCanvasSlot::layout()
    {
        
    }

    std::unique_ptr<ISlot> SCanvas::makeSlot(std::shared_ptr<SWidget> content)
    {
        return std::make_unique<CCanvasSlot>(this, std::move(content));
    }
}
