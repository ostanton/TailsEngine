#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <Tails/Config.hpp>

#ifdef TAILS_DEBUG
#include <iostream>

#define TailsAssert(condition, message) \
    (!static_cast<bool>(condition)) ? \
        (std::cerr << "Assertion failed: " << #condition << "\n" \
        << "Context: " << TAILS_FUNCTION << "\n" \
        << "In file \"" << __FILE__ << "\" on line " << __LINE__ << "\n" \
        << "Message: " << (message) << "\n", abort(), 0) : 1;
#else // TAILS_DEBUG
#define TailsAssert(condition, message)
#endif // TAILS_DEBUG

#endif // TAILS_ASSERT_HPP
