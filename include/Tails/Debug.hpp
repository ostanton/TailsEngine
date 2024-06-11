#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <string>
#include <iostream>

namespace tails
{
    class Debug
    {
    public:
        template<typename T>
        static void print(const T& s)
        {
            std::cout << s << "\n";
        }

        template<typename... ArgsT>
        static void print(const ArgsT&... s)
        {
            (std::cout << (s << ...)) << "\n";
        }

        template<typename... ArgsT>
        static void print(ArgsT&&... s)
        {
            (std::cout << (s << ...)) << "\n";
        }
    };
}

#endif // TAILS_DEBUG_HPP
