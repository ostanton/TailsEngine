#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#ifdef TAILS_DEBUG
#include <iostream>
#endif // TAILS_DEBUG

#ifdef TAILS_DEBUG
#define TailsAssert(condition, message) \
    std::cout << \
    (static_cast<bool>(condition) ? "Assertion failed: " << #condition << \
    "\n" << "In file " << __FILE__ << " on line " << __LINE__ << \
    "\nMessage: " << message : void(0));
#else
#define TailsAssert(condition, message) 0
#endif // TAILS_DEBUG

#endif // TAILS_ASSERT_HPP
