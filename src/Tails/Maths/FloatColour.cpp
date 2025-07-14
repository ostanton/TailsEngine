#include <Tails/Maths/FloatColour.hpp>
#include <Tails/Maths/Colour.hpp>

namespace tails
{
    const SFloatColour SFloatColour::red {1.f, 0.f, 0.f};
    const SFloatColour SFloatColour::yellow {1.f, 1.f, 0.f};
    const SFloatColour SFloatColour::green {0.f, 1.f, 0.f};
    const SFloatColour SFloatColour::cyan {0.f, 1.f, 1.f};
    const SFloatColour SFloatColour::blue {0.f, 0.f, 1.f};
    const SFloatColour SFloatColour::magenta {1.f, 0.f, 1.f};

    const SFloatColour SFloatColour::transparent {0.f, 0.f, 0.f, 0.f};
    const SFloatColour SFloatColour::white {1.f, 1.f, 1.f};
    const SFloatColour SFloatColour::black {0.f, 0.f, 0.f};

    SFloatColour::SFloatColour(const SColour colour) noexcept
        : r(static_cast<float>(colour.r) / 255.f)
        , g(static_cast<float>(colour.g) / 255.f)
        , b(static_cast<float>(colour.b) / 255.f)
        , a(static_cast<float>(colour.a) / 255.f)
    {}
}
