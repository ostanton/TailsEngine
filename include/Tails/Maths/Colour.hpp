#ifndef TAILS_COLOUR_HPP
#define TAILS_COLOUR_HPP

#include <Tails/Core.hpp>

namespace tails
{
    struct TAILS_API SColour final
    {
        u8 r {255};
        u8 g {255};
        u8 b {255};
        u8 a {255};

        static SColour red;
        static SColour yellow;
        static SColour green;
        static SColour cyan;
        static SColour blue;
        static SColour magenta;
        
        static SColour transparent;
        static SColour white;
        static SColour black;
    };
}

#endif // TAILS_COLOUR_HPP
