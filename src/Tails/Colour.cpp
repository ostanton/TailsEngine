#include <Tails/Types/Colour.hpp>

namespace tails
{
    SColour SColour::red {255, 0, 0};
    SColour SColour::yellow {255, 255, 0};
    SColour SColour::green {0, 255, 0};
    SColour SColour::cyan {0, 255, 255};
    SColour SColour::blue {0, 0, 255};
    SColour SColour::magenta {255, 0, 255};
    
    SColour SColour::transparent {0, 0, 0, 0};
    SColour SColour::white {};
    SColour SColour::grey {127, 127, 127};
    SColour SColour::black {0, 0, 0};
}
