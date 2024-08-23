#ifndef TAILS_WIDGETVIEWPORT_HPP
#define TAILS_WIDGETVIEWPORT_HPP

#include <Tails/Config.hpp>
#include <Tails/WidgetContainer.hpp>

namespace tails
{
    class CEngine;

    /**
     * Just a certain kind of container for now
     */
    class TAILS_API WViewport : public WContainer
    {
        void drawChild(size_t childIndex) const override {}
        std::unique_ptr<ISerialisable> clone() const override {return std::make_unique<WViewport>();}
    };
}

#endif // TAILS_WIDGETVIEWPORT_HPP
