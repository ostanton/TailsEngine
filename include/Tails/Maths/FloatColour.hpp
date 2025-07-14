#ifndef TAILS_FLOAT_COLOUR_HPP
#define TAILS_FLOAT_COLOUR_HPP

#include <Tails/Core.hpp>

#include <compare>

namespace tails
{
    struct SColour;

    /**
     * Colour structure which represents its channels as floating points from 0..1
     * (e.g. {1, 0, 0, 1} would be solid red)
     */
    struct TAILS_API SFloatColour final
    {
        float r {1.f};
        float g {1.f};
        float b {1.f};
        float a {1.f};

        constexpr SFloatColour() = default;
        constexpr SFloatColour(
            const float red,
            const float green,
            const float blue,
            const float alpha = 1.f
        )
            : r(red), g(green), b(blue), a(alpha)
        {}
        SFloatColour(SColour colour) noexcept;
        constexpr SFloatColour(const SFloatColour&) = default;
        constexpr SFloatColour(SFloatColour&&) noexcept = default;
        constexpr SFloatColour& operator=(const SFloatColour&) = default;
        constexpr SFloatColour& operator=(SFloatColour&&) noexcept = default;
        ~SFloatColour() = default;

        constexpr auto operator<=>(const SFloatColour&) const noexcept = default;

        static const SFloatColour red;
        static const SFloatColour yellow;
        static const SFloatColour green;
        static const SFloatColour cyan;
        static const SFloatColour blue;
        static const SFloatColour magenta;

        static const SFloatColour transparent;
        static const SFloatColour white;
        static const SFloatColour black;
    };
}

#endif // TAILS_FLOAT_COLOUR_HPP
