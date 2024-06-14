#ifndef TAILS_WIDGETNAVIGATION_HPP
#define TAILS_WIDGETNAVIGATION_HPP

#include <Tails/Config.hpp>

namespace tails
{
    class Widget;

    // TODO - could be turned into a subsystem??
    class TAILS_API WidgetNavigation
    {
    public:
        virtual void focusChanged(Widget* oldWidget, Widget* newWidget);
    };

} // tails

#endif //TAILS_WIDGETNAVIGATION_HPP
