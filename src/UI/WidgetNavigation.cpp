#include <Tails/UI/WidgetNavigation.hpp>
#include <Tails/UI/Widget.hpp>

#include <iostream>

namespace tails
{
    void WidgetNavigation::focusChanged(Widget* oldWidget, Widget* newWidget)
    {
        std::cout << "UI navigation changed, from " << oldWidget << " to " << newWidget << std::endl;
    }
} // tails
