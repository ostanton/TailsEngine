#ifndef TAILS_WIDGET_SLOT_HPP
#define TAILS_WIDGET_SLOT_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails::ui
{
    class CWidget;

    /**
     * Abstract base class for panel slots which define how their content widget should be laid out
     */
    struct TAILS_API ISlot
    {
        ISlot() = default;
        ISlot(CWidget* inOwner, std::shared_ptr<CWidget> inContent)
            : owner(inOwner), content(std::move(inContent))
        {}
        
        ISlot(const ISlot&) = default;
        ISlot(ISlot&&) = default;
        ISlot& operator=(const ISlot&) = default;
        ISlot& operator=(ISlot&&) = default;
        virtual ~ISlot() = default;

        CWidget* owner {nullptr};
        std::shared_ptr<CWidget> content;
    };
}

#endif // TAILS_WIDGET_SLOT_HPP
