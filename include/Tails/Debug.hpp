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
            // TODO - is this possible?? instead of separate overload?
            if ((sizeof...(args)) > 0)
                std::cout << (args << ...) << "\n";
            else
                std::cout << "\n";
#endif // NDEBUG
        }

        static void print()
        {
#ifndef NDEBUG
            std::cout << "\n";
#endif // NDEBUG
        }
    };
}

#endif // TAILS_DEBUG_HPP
