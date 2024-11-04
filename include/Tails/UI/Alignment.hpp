#ifndef TAILS_UI_ALIGNMENT_HPP
#define TAILS_UI_ALIGNMENT_HPP

#include <Tails/Config.hpp>

namespace tails::ui
{
    enum class EHorizontalAlignment : std::uint8_t
    {
        Left,
        Centre,
        Right,
        Fill
    };

    enum class EVerticalAlignment : std::uint8_t
    {
        Top,
        Centre,
        Bottom,
        Fill
    };
}

#endif // TAILS_UI_ALIGNMENT_HPP
