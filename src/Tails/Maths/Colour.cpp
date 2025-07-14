#include <Tails/Maths/Colour.hpp>
#include <Tails/Maths/FloatColour.hpp>

namespace tails
{
    const SColour SColour::red = {255, 0, 0};
    const SColour SColour::yellow {255, 255, 0};
    const SColour SColour::green {0, 255, 0};
    const SColour SColour::cyan {0, 255, 255};
    const SColour SColour::blue {0, 0, 255};
    const SColour SColour::magenta {255, 0, 255};

    const SColour SColour::transparent {0, 0, 0, 0};
    const SColour SColour::white {};
    const SColour SColour::black {0, 0, 0};

    SColour::SColour(const SFloatColour& colour) noexcept
        : r(static_cast<u8>(colour.r * 255))
        , g(static_cast<u8>(colour.g * 255))
        , b(static_cast<u8>(colour.b * 255))
        , a(static_cast<u8>(colour.a * 255))
    {}
}
