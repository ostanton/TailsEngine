#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Config.hpp>

#ifndef NDEBUG
#include <iostream>
#endif // NDEBUG

namespace tails
{
    class TAILS_API CDebug final
    {
    public:
        /**
         * Prints arguments via a comma-separated list to cout
         */
        template<typename... Args>
        static void print(Args&&... args)
        {
#ifdef TAILS_DEBUG
            // TODO - test for args == 0 isntead of separate overload?
            ((std::cout << std::forward<Args>(args)), ...) << "\n";
#endif // NDEBUG
        }

        /**
         * Prints a blank new line to cout
         */
        static void print()
        {
#ifdef TAILS_DEBUG
            std::cout << "\n";
#endif // NDEBUG
        }

        /**
         * Prints arguments via a comma-separated list to cerr,
         * with the line prefix "Error: "
         */
        template<typename... Args>
        static void error(Args&&... args)
        {
#ifdef TAILS_DEBUG
            std::cerr << "Error: ";
            ((std::cerr << std::forward<Args>(args)), ...) << "\n";
#endif // NDEBUG
        }
    };
}

#endif // TAILS_DEBUG_HPP
