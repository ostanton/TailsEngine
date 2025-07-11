#include <Tails/UI/WidgetSubsystem.hpp>
#include <Tails/UI/Layout/Canvas.hpp>
#include <Tails/UI/LayoutData.hpp>
#include <Tails/UI/TransformedWidgets.hpp>
#include <Tails/UI/Rendering/DrawElementList.hpp>
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

    void paint(const float deltaSeconds)
    {
        // TODO - get window input instead of renderer, get window layout data!
        SLayoutData layoutData;
        layoutData.transform.scale2D = 1.f;
        layoutData.size = render::getResolution();

        // Gather the widgets as draw element data, then render them
        CDrawElementList drawElements;
        gRootPanel->paint(layoutData, drawElements, deltaSeconds);

        for (const auto& element : drawElements)
        {
            if (element.texture)
                render::texture(
                    element.texture,
                    {element.position, 0.f, {1.f}},
                    element.size,
                    element.colour
                );
            else
                render::rect(
                    {element.position, 0.f, {1.f}},
                    element.size,
                    element.colour
                );
        }
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

    SSlotBase* addWidget(std::shared_ptr<CWidget> content)
    {
        return gRootPanel->addChild(std::move(content));
    }

    SSlotBase* setupWidget(std::shared_ptr<CWidget> content, const std::shared_ptr<CWidget>& parent)
    {
        return parent->getChildren().addChild(std::move(content));
    }
}
