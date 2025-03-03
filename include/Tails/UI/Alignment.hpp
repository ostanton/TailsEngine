#ifndef TAILS_UI_ALIGNMENT_HPP
#define TAILS_UI_ALIGNMENT_HPP

#include <Tails/Types/Int.hpp>

namespace tails::ui
{
    enum class EHorizontalAlignment : u8
    {
        Left,
        Centre,
        Right,
        Fill
    };

    enum class EVerticalAlignment : u8
    {
        Top,
        Centre,
        Bottom,
        Fill
    };
}

#endif // TAILS_UI_ALIGNMENT_HPP
