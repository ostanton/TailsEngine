#ifndef TAILS_ACTION_HANDLE_HPP
#define TAILS_ACTION_HANDLE_HPP

#include <Tails/Core.hpp>

namespace tails
{
    struct SAction;
    
    struct TAILS_API SActionHandle final
    {
        usize index;

        [[nodiscard]] SAction* getAction() const noexcept;
    };
}

#endif // TAILS_ACTION_HANDLE_HPP
