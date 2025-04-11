#include <Tails/SilverUI/WidgetSubsystem.hpp>
#include <Tails/SilverUI/Layout/Canvas.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Input/Event.hpp>

namespace tails::ui
{
    namespace
    {
        SCanvas gRootCanvas;
    }
    
    void init()
    {
        
    }

    void processEvent(const CEvent& ev)
    {
        // TODO - send event down widget tree
    }

    void tick(const float deltaSeconds)
    {
        gRootCanvas.onTick(deltaSeconds);
    }

    void render(IRenderer& renderer)
    {
        renderer.render(gRootCanvas);
    }

    ISlot* addWidget(std::shared_ptr<SWidget> content)
    {
        return gRootCanvas.addChild(std::move(content));
    }
}
