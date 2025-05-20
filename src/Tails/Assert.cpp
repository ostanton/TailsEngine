#include <Tails/Assert.hpp>

#include <iostream>

namespace tails::impl
{
    void throwAssert(
        const char* condition,
        const char* message,
        const char* function,
        const char* file,
        const int line
    )
    {
#ifdef TAILS_ENABLE_ASSERTS
        std::cerr
            << "Tails: Assertion failed: " << condition << '\n' \
            << "       Context: " << function << '\n' \
            << "       In file \"" << file << "\" on line " << line << '\n' \
            << "       Message: " << message << '\n';

        abort();
#endif // TAILS_ENABLE_ASSERTS
    }
}
