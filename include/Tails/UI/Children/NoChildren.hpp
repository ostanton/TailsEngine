#ifndef TAILS_NO_CHILDREN_HPP
#define TAILS_NO_CHILDREN_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Children/Children.hpp>

namespace tails::ui
{
    struct TAILS_API SNoChildren final : IChildren
    {
        using IChildren::IChildren;
        
        [[nodiscard]] usize size() const noexcept override {return 0;}
        [[nodiscard]] const SSlotBase* getSlotAt(usize index) const noexcept override {return nullptr;}
        [[nodiscard]] std::shared_ptr<CWidget> getChildAt(usize index) noexcept override {return nullptr;}
        [[nodiscard]] std::shared_ptr<const CWidget> getChildAt(usize index) const noexcept override {return nullptr;}

        SSlotBase* addChild(std::shared_ptr<CWidget> child) override {return nullptr;}
        void clearChildren() override {}
    };
}

#endif // TAILS_NO_CHILDREN_HPP
