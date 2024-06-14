#ifndef TAILS_CANVASPANEL_HPP
#define TAILS_CANVASPANEL_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/PanelWidget.hpp>

namespace tails
{
    class CanvasSlot;

    class TAILS_API CanvasPanel : public PanelWidget
    {
    public:
        template<typename T>
        CanvasSlot* addChildToCanvas()
        {
            return static_cast<CanvasSlot*>(addChild<T>());
        }

        CanvasSlot* addChildToCanvas(std::unique_ptr<Widget> content);
    };
}

#endif //TAILS_CANVASPANEL_HPP
