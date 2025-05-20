#ifndef TAILS_WIDGET_SUBSYSTEM_HPP
#define TAILS_WIDGET_SUBSYSTEM_HPP

#include <Tails/Core.hpp>
#include <Tails/Concepts.hpp>

#include <memory>

namespace tails
{
    class CEvent;
}

/**
 * Originally called SilverUI, now just UI, as it's shorter. So no more Silver :(
 *
 * Very inspired by Unreal Engine's Slate, where widgets have slots which hold layout properties
 * (like margin, size, alignment, etc.). In a widget's onPaint function, it first lays out its
 * children, populating a CTransformedWidgets object, which is then iterated over and onPaint
 * is called in those laid-out children. You can see this in CPanel::onPaint. SLayoutData stores
 * a widget's spatial information, like its transform, size, etc. This is used when rendering
 * a widget. Non-panel widgets don't calculate children layouts, as they have no children (if they
 * inherit the CLeafWidget class that is), so they just render something with the specified
 * myLayout parameter, which is the spatial information for this widget. Widgets do not know
 * anything about their environment or the space they occupy, that is all calculated every frame
 * with SLayoutData. Therefore, both SLayoutData and CTransformedWidgets are very temporary
 * objects, and should not be stored for longer than the function in which they are passed into (just
 * don't store them anywhere!).
 *
 * A good example of a simple panel to lay out its contents for is the CCanvas, where child widgets
 * have a position and an overridable size. CImage is a nice example of a leaf widget which has no
 * children and only renders a texture or a coloured rect.
 */

namespace tails::ui
{
    class CWidget;
    class CPanel;
    struct ISlot;
    
    TAILS_API void init();
    TAILS_API void processEvent(const CEvent& ev);
    TAILS_API void paint(float deltaSeconds);
    TAILS_API void deinit();

    [[nodiscard]] TAILS_API const std::shared_ptr<CPanel>& getRootPanel() noexcept;
    
    TAILS_API ISlot* addWidget(std::shared_ptr<CWidget> content);
    TAILS_API ISlot* setupWidget(std::shared_ptr<CWidget> content, const std::shared_ptr<CWidget>& parent);
    
    template<DerivedFrom<CPanel> ParentT>
    typename ParentT::SSlot* setupWidget(
        std::shared_ptr<CWidget> content,
        const std::shared_ptr<ParentT>& parent
    )
    {
        return static_cast<typename ParentT::SSlot*>(setupWidget(std::move(content), parent));
    }

    template<DerivedFrom<CWidget> T>
    std::shared_ptr<T> createWidget(const std::shared_ptr<CWidget>& parent)
    {
        auto widget = std::make_shared<T>();
        if (parent)
            setupWidget(widget, parent);
        return widget;
    }
    
    template<DerivedFrom<CWidget> T>
    ISlot* addWidget()
    {
        return addWidget(std::make_shared<T>());
    }
}

#endif // TAILS_WIDGET_SUBSYSTEM_HPP
