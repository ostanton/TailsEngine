#ifndef TAILS_CANVASSLOT_HPP
#define TAILS_CANVASSLOT_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/PanelSlot.hpp>
#include <Tails/UI/Layout/Anchors.hpp>
#include <Tails/UI/Layout/Margin.hpp>

namespace tails
{
    class TAILS_API CanvasSlot : public PanelSlot
    {
    public:
        CanvasSlot(PanelWidget* parent, std::unique_ptr<Widget> content);

        Margin offsets;
        Anchors anchors;
        sf::Vector2f alignment;
        bool autoSize {false};
        int zOrder {0};
    };

} // tails

#endif //TAILS_CANVASSLOT_HPP
