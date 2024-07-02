#include <TestGame/MyScreen.hpp>
#include <Tails/UI/CanvasPanel.hpp>
#include <Tails/UI/RectangleWidget.hpp>
#include <Tails/UI/CanvasSlot.hpp>

void MyScreen::init(State& state)
{
    ScreenLayer::init(state);

    auto canvas = setContent<CanvasPanel>();
    auto canvasSlot = canvas->addChildToCanvas<RectangleWidget>();
    canvasSlot->getContent()->setSize(64.f, 8.f);
    dynamic_cast<RectangleWidget*>(canvasSlot->getContent())->getRectangle().setFillColor(sf::Color::Red);
}
