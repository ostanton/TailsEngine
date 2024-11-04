#ifndef TAILS_WIDGETVIEWPORT_HPP
#define TAILS_WIDGETVIEWPORT_HPP

#include <Tails/Config.hpp>
#include <Tails/UI/WidgetContainer.hpp>

namespace tails
{
    class CEngine;

    /**
     * Just a certain kind of container for now
     */
    class TAILS_API WViewport : public WContainer
    {
        void drawChild(size_t childIndex) const override {}
    };
}

#endif // TAILS_WIDGETVIEWPORT_HPP
