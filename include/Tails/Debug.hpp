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
        template<typename... Args>
        static void print(Args... args)
        {
#ifndef NDEBUG
            std::cout << (args << ...) << "\n";
#endif // NDEBUG
        }
    };
}

#endif // TAILS_DEBUG_HPP
