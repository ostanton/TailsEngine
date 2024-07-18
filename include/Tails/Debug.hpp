#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Config.hpp>

#include <string>
#include <iostream>

namespace tails
{
    class TAILS_API Debug
    {
    public:
        template<typename T>
        static void print(const T& s)
        {
#ifdef TAILS_DEBUG
            std::cout << s << "\n";
#endif
        }

        template<typename... ArgsT>
        static void print(const ArgsT&... s)
        {
#ifdef TAILS_DEBUG
            (std::cout << (s << ...)) << "\n";
#endif
        }

        template<typename... ArgsT>
        static void print(ArgsT&&... s)
        {
#ifdef TAILS_DEBUG
            (std::cout << (std::forward<ArgsT>(s) << ...)) << "\n";
#endif
        }
    };
}

#endif // TAILS_DEBUG_HPP
