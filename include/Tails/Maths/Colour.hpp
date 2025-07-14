#ifndef TAILS_COLOUR_HPP
#define TAILS_COLOUR_HPP

#include <Tails/Core.hpp>

#include <compare>

namespace tails
{
    struct SFloatColour;

    /**
     * Basic colour structure which stores colours as 8-bit unsigned integers
     */
    struct TAILS_API SColour final
    {
        u8 r {255};
        u8 g {255};
        u8 b {255};
        u8 a {255};

        constexpr SColour() = default;
        constexpr SColour(
            const u8 red,
            const u8 green,
            const u8 blue,
            const u8 alpha = 255
        )
            : r(red), g(green), b(blue), a(alpha)
        {}
        // explicit conversion constructor as it's a narrowing conversion
        explicit SColour(const SFloatColour& colour) noexcept;
        constexpr SColour(const SColour&) = default;
        constexpr SColour(SColour&&) noexcept = default;
        constexpr SColour& operator=(const SColour&) = default;
        constexpr SColour& operator=(SColour&&) noexcept = default;
        constexpr ~SColour() = default;

        constexpr auto operator<=>(const SColour&) const noexcept = default;

        static const SColour red;
        static const SColour yellow;
        static const SColour green;
        static const SColour cyan;
        static const SColour blue;
        static const SColour magenta;

        static const SColour transparent;
        static const SColour white;
        static const SColour black;
    };
}

#endif // TAILS_COLOUR_HPP
