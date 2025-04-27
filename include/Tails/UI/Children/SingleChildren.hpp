#ifndef TAILS_SINGLE_CHILDREN_HPP
#define TAILS_SINGLE_CHILDREN_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Children/Children.hpp>
#include <Tails/Concepts.hpp>

namespace tails::ui
{
    struct ISlot;
    
    template<DerivedFrom<ISlot> SlotT>
    struct TAILS_API TSingleChildren final : IChildren
    {
        TSingleChildren(CWidget* inOwner, std::shared_ptr<CWidget> content)
            : IChildren(inOwner), slot(inOwner, std::move(content))
        {}

        [[nodiscard]] usize size() const noexcept override {return 1;}
        [[nodiscard]] const ISlot* getSlotAt(const usize index) const noexcept override
        {
            return &slot;
        }
        [[nodiscard]] std::shared_ptr<CWidget> getChildAt(usize index) noexcept override
        {
            return slot.content;
        }
        [[nodiscard]] std::shared_ptr<const CWidget> getChildAt(usize index) const noexcept override
        {
            return slot.content;
        }

        ISlot* addChild(std::shared_ptr<CWidget> child) override
        {
            slot.content = std::move(child);
            return &slot;
        }

        void clearChildren() override
        {
            slot.content.reset();
        }

        [[nodiscard]] const std::shared_ptr<CWidget>& getContent() const noexcept
        {
            return slot.content;
        }

        SlotT slot;
    };
}

#endif // TAILS_SINGLE_CHILDREN_HPP
