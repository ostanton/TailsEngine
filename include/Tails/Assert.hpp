#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <Tails/Config.hpp>

#ifdef TAILS_DEBUG
#include <iostream>

#define TAILS_ASSERT(condition, message) \
    (!static_cast<bool>(condition)) ? \
        (std::cerr << "Assertion failed: " << #condition << "\n" \
        << "Context: " << tails::getFunctionName() << "\n" \
        << "In file \"" << tails::getFileName() << "\" on line " << tails::getLine() << "\n" \
        << "Message: " << (message) << "\n", abort(), 0) : 1
#else // TAILS_DEBUG
#define TAILS_ASSERT(condition, message)
#endif // TAILS_DEBUG

namespace tails
{
    // future possible assert function
    /*
    template<typename Pred, typename T>
    constexpr void assert(Pred predicate, T msg)
    {
        if (!predicate())
        {
            
        }
    }
    */
}

#endif // TAILS_ASSERT_HPP
