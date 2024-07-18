#include <Tails/UI/CanvasPanel.hpp>
#include <Tails/UI/CanvasSlot.hpp>

namespace tails
{

    CanvasSlot* CanvasPanel::addChildToCanvas(std::unique_ptr<Widget> content)
    {
        return addChild<CanvasSlot>(std::move(content));
    }
} // tails
