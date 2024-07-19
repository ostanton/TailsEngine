#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <Tails/Config.hpp>

#include <iostream>

// Found this on stack overflow, will prove useful!
// Modified to show pretty function and generally look nicer in the terminal
// https://stackoverflow.com/questions/3767869/adding-message-to-assert
// NOTE - Might need to wrap __FILE__ and __LINE__ in TAILS_FILE & TAILS_LINE respectively if there is varying
// compiler support (such as __PRETTY_FUNCTION__, etc.)
#ifdef TAILS_DEBUG
#define TailsAssert(condition, message)\
    (!(condition)) ?\
        (std::cerr << "Assertion failed: (" << #condition << ")\n"\
        << "Context: " << TAILS_FUNCTION << "\n"\
        << __FILE__\
        << ", line " << __LINE__ << "."\
        << "\n" << "Reason: " << (message) << "\n", abort(), 0) : 1
#else
#define TailsAssert(condition, message) 0
#endif

#endif //TAILS_ASSERT_HPP
