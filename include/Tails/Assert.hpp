#ifndef TAILS_ASSERT_HPP
#define TAILS_ASSERT_HPP

#include <Tails/Config.hpp>

#ifdef TAILS_DEBUG
#include <iostream>
#include <Tails/Concepts.hpp>

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
#ifdef TAILS_DEBUG
    namespace priv
    {
        template<PrintableStream MsgT>
        constexpr void invokeAssert(const MsgT& msg, const std::source_location& loc = std::source_location::current())
        {
            std::cerr << "Assertion failed!\n"
                << "Context: " << getFunctionName(loc) << "\n"
                << "In file \"" << getFileName(loc) << "\" on line " << getLine(loc) << "\n"
                << "Message: " << msg << "\n";
            abort();
        }
    } // priv
#endif // TAILS_DEBUG

#ifdef TAILS_DEBUG
    template<std::predicate<> PredT, PrintableStream MsgT>
#else // TAILS_DEBUG
    template<typename PredT, typename MsgT>
#endif // TAILS_DEBUG
    constexpr void runtimeAssert(PredT predicate, MsgT&& msg, const std::source_location& loc = std::source_location::current())
    {
#ifdef TAILS_DEBUG
        if (!predicate()) priv::invokeAssert(std::forward<MsgT>(msg), loc);
#endif // TAILS_DEBUG
    }

#ifdef TAILS_DEBUG
    template<PrintableStream MsgT>
#else // TAILS_DEBUG
    template<typename MsgT>
#endif // TAILS_DEBUG
    constexpr void runtimeAssert(bool condition, MsgT&& msg, const std::source_location& loc = std::source_location::current())
    {
#ifdef TAILS_DEBUG
        if (!condition) priv::invokeAssert(std::forward<MsgT>(msg), loc);
#endif // TAILS_DEBUG
    }
} // tails

#endif // TAILS_ASSERT_HPP
