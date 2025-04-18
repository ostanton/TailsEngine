#ifndef TAILS_PANEL_CHILDREN_HPP
#define TAILS_PANEL_CHILDREN_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Children/Children.hpp>

#include <vector>

namespace tails::ui
{
    template<typename SlotT>
    struct TAILS_API TPanelChildren final : IChildren
    {
        using Iterator = typename std::vector<SlotT>::iterator;
        using ConstIterator = typename std::vector<SlotT>::const_iterator;

        using IChildren::IChildren;
        
        [[nodiscard]] usize size() const noexcept override {return slots.size();}
        [[nodiscard]] const ISlot* getSlotAt(const usize index) const noexcept override {return &slots[index];}
        
        [[nodiscard]] std::shared_ptr<CWidget> getChildAt(const usize index) noexcept override
        {
            return getSlotAt(index)->content;
        }
        
        [[nodiscard]] std::shared_ptr<const CWidget> getChildAt(const usize index) const noexcept override
        {
            return getSlotAt(index)->content;
        }

        ISlot* addChild(std::shared_ptr<CWidget> child) override
        {
            slots.emplace_back(owner, std::move(child));
            slots.back().content->slot = &slots.back();
            return &slots.back();
        }

        [[nodiscard]] Iterator begin() noexcept {return slots.begin();}
        [[nodiscard]] Iterator end() noexcept {return slots.end();}
        [[nodiscard]] ConstIterator begin() const noexcept {return slots.begin();}
        [[nodiscard]] ConstIterator end() const noexcept {return slots.end();}
        
        std::vector<SlotT> slots;
    };
}

#endif // TAILS_PANEL_CHILDREN_HPP
