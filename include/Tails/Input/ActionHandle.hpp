#ifndef TAILS_ACTION_HANDLE_HPP
#define TAILS_ACTION_HANDLE_HPP

#include <Tails/Core.hpp>

namespace tails::input
{
    struct SAction;

    /**
     * Handle for an input action. It's just an index with a helper function to
     * get the action it's a handle for
     */
    struct TAILS_API SActionHandle final
    {
        usize index;

        [[nodiscard]] SAction* getAction() const noexcept;
    };
}

#endif // TAILS_ACTION_HANDLE_HPP
