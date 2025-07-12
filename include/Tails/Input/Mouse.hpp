#ifndef TAILS_MOUSE_HPP
#define TAILS_MOUSE_HPP

#include <Tails/Core.hpp>

namespace tails::mouse
{
    enum class EButton : u8
    {
        Left = 1,
        Middle,
        Right,
        Special1,
        Special2
    };

    enum class EAxis : u8
    {
        X,
        Y,
    };

    enum class EScrollDirection : u8
    {
        Up,
        Down,
    };
}

#endif // TAILS_MOUSE_HPP
