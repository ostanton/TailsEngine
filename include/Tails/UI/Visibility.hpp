#ifndef TAILS_WIDGET_VISIBILITY_HPP
#define TAILS_WIDGET_VISIBILITY_HPP

#include <Tails/Core.hpp>

namespace tails::ui
{
    enum class EVisibility : u8
    {
        Visible,

        /** Not visible but still takes up layout space */
        Hidden,

        /** Hidden whilst not taking up layout space */
        Collapsed,
    };
}

#endif // TAILS_WIDGET_VISIBILITY_HPP
