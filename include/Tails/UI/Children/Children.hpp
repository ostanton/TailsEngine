#ifndef TAILS_WIDGET_CHILDREN_HPP
#define TAILS_WIDGET_CHILDREN_HPP

#include <Tails/Core.hpp>

#include <memory>

namespace tails::ui
{
    struct SSlotBase;
    class CWidget;
    
    /**
     * Interface for implementation-defined widget children. Most panels use TPanelChildren for example
     */
    struct TAILS_API IChildren
    {
        IChildren() = delete;
        explicit IChildren(CWidget* inOwner)
            : owner(inOwner)
        {}
        IChildren(const IChildren&) = default;
        IChildren(IChildren&&) = default;
        IChildren& operator=(const IChildren&) = default;
        IChildren& operator=(IChildren&&) = default;
        virtual ~IChildren() = default;

        [[nodiscard]] virtual usize size() const noexcept = 0;
        [[nodiscard]] virtual const SSlotBase* getSlotAt(usize index) const noexcept = 0;
        [[nodiscard]] virtual std::shared_ptr<CWidget> getChildAt(usize index) noexcept = 0;
        [[nodiscard]] virtual std::shared_ptr<const CWidget> getChildAt(usize index) const noexcept = 0;

        virtual SSlotBase* addChild(std::shared_ptr<CWidget> child) = 0;
        virtual void clearChildren() = 0;

        CWidget* owner;
    };
}

#endif // TAILS_WIDGET_CHILDREN_HPP
