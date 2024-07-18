#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <iostream>

// Found this on stack overflow, will prove useful!
// Modified to show pretty function and generally look nicer in the terminal
// https://stackoverflow.com/questions/3767869/adding-message-to-assert
#ifdef NDEBUG
#define TailsAssert(condition, message) 0
#else
#define TailsAssert(condition, message)\
   (!(condition)) ?\
      (std::cerr << "Assertion failed: (" << #condition << ")\n"\
      << "Context: " << __FUNCTION__ << "\n"\
      << __FILE__\
      << ", line " << __LINE__ << "."\
      << "\n" << "Reason: " << message << "\n", abort(), 0) : 1
#endif

#endif //TAILS_ASSERT_HPP
