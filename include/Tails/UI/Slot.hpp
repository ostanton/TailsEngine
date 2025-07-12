#ifndef TAILS_WIDGET_SLOT_HPP
#define TAILS_WIDGET_SLOT_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails::ui
{
    class CWidget;

    /**
     * Base class for panel slots which define how their content widget should be laid out
     */
    struct TAILS_API SSlotBase
    {
        SSlotBase() = delete;
        SSlotBase(CWidget* inOwner, std::shared_ptr<CWidget> inContent)
            : owner(inOwner), content(std::move(inContent))
        {}

        SSlotBase(const SSlotBase&) = default;
        SSlotBase(SSlotBase&&) = default;
        SSlotBase& operator=(const SSlotBase&) = default;
        SSlotBase& operator=(SSlotBase&&) = default;
        virtual ~SSlotBase() = default;

        CWidget* owner;
        std::shared_ptr<CWidget> content;
    };
}

#endif // TAILS_WIDGET_SLOT_HPP
