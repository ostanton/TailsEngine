#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/TransformedWidgets.hpp>
#include <Tails/Renderer/Renderer.hpp>
#include <Tails/Log.hpp>

namespace tails::ui
{
    namespace
    {
        std::shared_ptr<CPanel> gRootPanel;
    }
    
    void init()
    {
        gRootPanel = std::make_shared<CCanvas>();
        
        TAILS_LOG(WidgetSubsystem, Message, "Initialised");
    }

    void processEvent(const CEvent& ev)
    {
        // TODO - send event down widget tree
    }

    void paint(const CRenderer& renderer, const float deltaSeconds)
    {
        // TODO - get window input instead of renderer, get window layout data!
        SLayoutData layoutData;
        layoutData.size = renderer.getRenderResolution();
        gRootPanel->paint(layoutData, renderer, deltaSeconds);
    }

    void deinit()
    {
        gRootPanel.reset();

        TAILS_LOG(WidgetSubsystem, Message, "Deinitialised");
    }

    const std::shared_ptr<CPanel>& getRootPanel() noexcept
    {
        return gRootPanel;
    }

    ISlot* addWidget(std::shared_ptr<CWidget> content)
    {
        return gRootPanel->addChild(std::move(content));
    }

    ISlot* setupWidget(std::shared_ptr<CWidget> content, const std::shared_ptr<CWidget>& parent)
    {
        return parent->getChildren().addChild(std::move(content));
    }
}
