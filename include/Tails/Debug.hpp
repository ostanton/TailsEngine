#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Config.hpp>

#ifdef TAILS_DEBUG
#include <Tails/Concepts.hpp>

#include <iostream>
#include <format>
#endif // TAILS_DEBUG

namespace tails
{
    class TAILS_API CDebug final
    {
    public:
        /**
         * Prints arguments via a comma-separated list to cout
         */
        template<
#ifdef TAILS_DEBUG
                PrintableStreamAll
#else // TAILS_DEBUG
                typename
#endif // TAILS_DEBUG
                ... Args>
        static void print(Args&&... args)
        {
#ifdef TAILS_DEBUG
            // TODO - test for args == 0 isntead of separate overload?
            ((std::cout << std::forward<Args>(args)), ...) << "\n";
#endif // TAILS_DEBUG
        }

        /**
         * Prints a blank new line to cout
         */
        static void print()
        {
#ifdef TAILS_DEBUG
            std::cout << std::endl;
#endif // TAILS_DEBUG
        }

        /**
         * Prints arguments via a comma-separated list to cerr,
         * with the line prefix "Error: "
         */
        template<
#ifdef TAILS_DEBUG
                PrintableStreamAll
#else // TAILS_DEBUG
                typename
#endif // TAILS_DEBUG
                ... Args>
        static void error(Args&&... args)
        {
#ifdef TAILS_DEBUG
            std::cerr << "Error: ";
            ((std::cerr << std::forward<Args>(args)), ...) << "\n";
#endif // TAILS_DEBUG
        }

        template<typename... ArgsT>
        static void printf(std::string_view string, ArgsT&&... args)
        {
#ifdef TAILS_DEBUG
            std::cout << std::vformat(string, std::make_format_args(args...)) << std::endl;
#endif // TAILS_DEBUG
        }
    };
}

#endif // TAILS_DEBUG_HPP
