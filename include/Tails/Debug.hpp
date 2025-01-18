#ifndef TAILS_DEBUG_HPP
#define TAILS_DEBUG_HPP

#include <Tails/Config.hpp>

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

#include <string_view>

#ifdef TAILS_DEBUG
#include <Tails/Concepts.hpp>

#include <iostream>
#include <format>
#endif // TAILS_DEBUG

namespace tails
{
    class CLevel;
}

namespace tails::debug
{
    /**
     * Prints arguments via a comma-separated list to cout
     */
    template<
#ifdef TAILS_DEBUG
            PrintableStreamAll
#else // TAILS_DEBUG
            typename
#endif // TAILS_DEBUG
            ... ArgsT>
    constexpr void print(ArgsT&&... args)
    {
#ifdef TAILS_DEBUG
        if constexpr (sizeof...(ArgsT) > 0)
            ((std::cout << std::forward<ArgsT>(args)), ...) << '\n';
        else
            std::cout << '\n';
#endif // TAILS_DEBUG
    }

    /**
     * Prints arguments via a comma-separated list to cerr,
     * with the line prefix "Error: "
     */
    template<
#ifdef TAILS_DEBUG
            PrintableStreamAll
#else // TAILS_DEBUG
            typename
#endif // TAILS_DEBUG
            ... ArgsT>
    constexpr void error(ArgsT&&... args)
    {
#ifdef TAILS_DEBUG
        if constexpr (sizeof...(ArgsT) > 0)
        {
            std::cerr << "Error: ";
            ((std::cerr << std::forward<ArgsT>(args)), ...) << '\n';
        }
        else
            std::cerr << "Error (unexplained)" << '\n';
#endif // TAILS_DEBUG
    }

    template<typename... ArgsT>
    void printf(const std::string_view string, ArgsT&&... args)
    {
#ifdef TAILS_DEBUG
        std::cout << std::vformat(string, std::make_format_args(args...)) << '\n';
#endif // TAILS_DEBUG
    }

    template<
#ifdef TAILS_DEBUG
            PrintableStreamAll
#else // TAILS_DEBUG
            typename
#endif // TAILS_DEBUG
            ... ArgsT>
    constexpr void exception(ArgsT&&... args)
    {
#ifdef TAILS_DEBUG
        std::cerr << "Exception: ";
        ((std::cerr << std::forward<ArgsT>(args)), ...) << '\n';
#endif // TAILS_DEBUG
    }

    void flush();
    void flushErr();

#ifdef TAILS_DEBUG
    struct TAILS_API SRect final
    {
        sf::FloatRect rect;
        sf::Color fillColour;
        sf::Color outlineColour;
        float thickness;
    };

    struct TAILS_API SLine final
    {
        sf::Vector2f start;
        sf::Vector2f end;
        sf::Color colour;
        float thickness;
    };

    struct TAILS_API SCircle final
    {
        sf::Vector2f position;
        float radius;
        std::size_t pointCount;
        sf::Color fillColour;
        sf::Color outlineColour;
        float thickness;
    };

    struct TAILS_API SConvex final
    {
        std::vector<sf::Vector2f> points;
        sf::Vector2f position;
        sf::Color fillColour;
        sf::Color outlineColour;
        float thickness;
    };
    
    /**
     * Gets the active rects. This is not available when not in a debug build!
     * @return Current active rects
     */
    TAILS_API const std::vector<SRect>& getRects() noexcept;
    
    /**
     * Gets the active lines. This is not available when not in a debug build!
     * @return Current active lines
     */
    TAILS_API const std::vector<SLine>& getLines() noexcept;

    /**
     * Gets the active circles. This is not available when not in a debug build!
     * @return Current active circles
     */
    TAILS_API const std::vector<SCircle>& getCircles() noexcept;

    /**
     * Gets the active convex shapes. This is not available when not in a debug build!
     * @return Current active convex shapes
     */
    TAILS_API const std::vector<SConvex>& getConvexShapes() noexcept;
#endif // TAILS_DEBUG
    
    TAILS_API void drawRect(
        sf::FloatRect rect,
        sf::Color fillColour = sf::Color::Transparent,
        sf::Color outlineColour = sf::Color::Red,
        float thickness = 1.f
    );
    TAILS_API void drawLine(
        sf::Vector2f start,
        sf::Vector2f end,
        sf::Color colour = sf::Color::Red,
        float thickness = 1.f
    );
    TAILS_API void drawCircle(
        sf::Vector2f position,
        float radius,
        std::size_t pointCount = 30,
        sf::Color fillColour = sf::Color::Transparent,
        sf::Color outlineColour = sf::Color::Red,
        float thickness = 1.f
    );
    TAILS_API void drawConvexShape(
        std::vector<sf::Vector2f> points,
        sf::Vector2f position,
        sf::Color fillColour = sf::Color::Transparent,
        sf::Color outlineColour = sf::Color::Red,
        float thickness = 1.f
    );

    /**
     * This is called by the engine, to clean up any lingering data after a frame
     */
    TAILS_API void cleanup();
}

#endif // TAILS_DEBUG_HPP
