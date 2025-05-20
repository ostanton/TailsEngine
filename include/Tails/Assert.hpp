#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <Tails/Core.hpp>

namespace tails::impl
{
    /** Throws an assertion */
    [[noreturn]] TAILS_API void throwAssert(
        const char* condition,
        const char* message,
        const char* function,
        const char* file,
        int line
    );
}

#ifdef TAILS_ENABLE_ASSERTS
    /**
     * Asserts if the condition evaluates to false, printing why with a message
     * @param COND Assert condition. Resolves to a boolean
     * @param MSG Error message
     */
    #define TAILS_ASSERT(COND, MSG) \
        (!static_cast<bool>(COND)) ? \
            (::tails::impl::throwAssert(#COND, MSG, TAILS_FUNCTION_NAME, TAILS_FILE_NAME, TAILS_LINE)) : (void)0
#else // TAILS_ENABLE_ASSERTS
    #define TAILS_ASSERT(COND, MSG)
#endif // TAILS_ENABLE_ASSERTS

#endif // TAILS_ASSERT_HPP
