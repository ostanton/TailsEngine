#ifndef TAILS_PANEL_CHILDREN_HPP
#define TAILS_PANEL_CHILDREN_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Children/Children.hpp>
#include <Tails/Concepts.hpp>

#include <deque>

namespace tails::ui
{
    struct SSlotBase;
    
    template<DerivedFrom<SSlotBase> SlotT>
    struct TAILS_API TPanelChildren final : IChildren
    {
        using SlotContainer = std::deque<SlotT>;
        using Iterator = typename SlotContainer::iterator;
        using ConstIterator = typename SlotContainer::const_iterator;

        using IChildren::IChildren;

        [[nodiscard]] usize size() const noexcept override {return slots.size();}
        [[nodiscard]] const SSlotBase* getSlotAt(const usize index) const noexcept override {return &slots[index];}

        [[nodiscard]] std::shared_ptr<CWidget> getChildAt(const usize index) noexcept override
        {
            return getSlotAt(index)->content;
        }

        [[nodiscard]] std::shared_ptr<const CWidget> getChildAt(const usize index) const noexcept override
        {
            return getSlotAt(index)->content;
        }

        SSlotBase* addChild(std::shared_ptr<CWidget> child) override
        {
            slots.emplace_back(owner, std::move(child));
            slots.back().content->slot = &slots.back();
            return &slots.back();
        }

        void clearChildren() override
        {
            slots.clear();
        }

        [[nodiscard]] Iterator begin() noexcept {return slots.begin();}
        [[nodiscard]] Iterator end() noexcept {return slots.end();}
        [[nodiscard]] ConstIterator begin() const noexcept {return slots.begin();}
        [[nodiscard]] ConstIterator end() const noexcept {return slots.end();}

        /**
         * deque and not vector because vectors invalidate when resizing, and I don't want more
         * pointer stuff, like vector<unique_ptr<SlotT>>
         */
        SlotContainer slots;
    };
}

#endif // TAILS_PANEL_CHILDREN_HPP
