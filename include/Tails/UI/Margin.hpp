#ifndef TAILS_MARGIN_HPP
#define TAILS_MARGIN_HPP

#include <Tails/Core.hpp>
#include <Tails/UI/Orientation.hpp>

namespace tails::ui
{
    struct TAILS_API SMargin final
    {
        SMargin() = default;
        SMargin(const float inLeft, const float inTop, const float inRight, const float inBottom) noexcept
            : left(inLeft), top(inTop), right(inRight), bottom(inBottom)
        {}
        SMargin(const float horizontal, const float vertical) noexcept
            : left(horizontal), top(vertical), right(horizontal), bottom(vertical)
        {}
        SMargin(const float uniform)
            : left(uniform), top(uniform), right(uniform), bottom(uniform)
        {}

        [[nodiscard]] float getWidth() const noexcept {return left + right;}
        [[nodiscard]] float getHeight() const noexcept {return top + bottom;}

        template<EOrientation Orientation>
        [[nodiscard]] float getSpaceAlong() const noexcept
        {
            if constexpr (Orientation == EOrientation::Vertical)
                return getHeight();
            else
                return getWidth();
        }
        
        float left {0.f};
        float top {0.f};
        float right {0.f};
        float bottom {0.f};
    };
}

#endif // TAILS_MARGIN_HPP
