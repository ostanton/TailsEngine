#include <Tails/UI/WidgetNavigation.hpp>
#include <Tails/UI/Widget.hpp>

#include <iostream>

namespace tails
{
    void WidgetNavigation::setFocus(Widget* widget)
    {
        // set widget pointers
        lastFocusedWidget = focusedWidget;
        focusedWidget = widget;

        // broadcast the focus and un-focus events
        lastFocusedWidget->getUnFocusEvent().broadcast(lastFocusedWidget);
        focusedWidget->getFocusEvent().broadcast(focusedWidget);

        // call the virtual focusChanged method for custom implementations
        focusChanged(lastFocusedWidget, focusedWidget);
    }

    bool WidgetNavigation::widgetHasFocus(Widget* widget)
    {
        return focusedWidget == widget;
    }

    void WidgetNavigation::focusChanged(Widget* oldWidget, Widget* newWidget)
    {
        std::cout << "UI navigation changed, from " << oldWidget << " to " << newWidget << std::endl;
    }
} // tails
