#include <Tails/Debug.hpp>

namespace tails::debug
{
    void flush()
    {
#ifdef TAILS_DEBUG
        std::flush(std::cout);
#endif // TAILS_DEBUG
    }

    void flushErr()
    {
#ifdef TAILS_DEBUG
        std::flush(std::cerr);
#endif // TAILS_DEBUG
    }

#ifdef TAILS_DEBUG
    struct SDebugShapes
    {
        std::vector<SRect> rects;
        std::vector<SLine> lines;
        std::vector<SCircle> circles;
        std::vector<SConvex> convex;

        void clear()
        {
            rects.clear();
            lines.clear();
            circles.clear();
            convex.clear();
        }
    } gDebugShapes;

    const std::vector<SRect>& getRects() noexcept {return gDebugShapes.rects;}
    const std::vector<SLine>& getLines() noexcept {return gDebugShapes.lines;}
    const std::vector<SCircle>& getCircles() noexcept {return gDebugShapes.circles;}
    const std::vector<SConvex>& getConvexShapes() noexcept {return gDebugShapes.convex;}
#endif // TAILS_DEBUG

    void drawRect(
        const sf::FloatRect rect,
        const sf::Color fillColour,
        const sf::Color outlineColour,
        const float thickness
    )
    {
#ifdef TAILS_DEBUG
        gDebugShapes.rects.emplace_back(rect, fillColour, outlineColour, thickness);
#endif // TAILS_DEBUG
    }

    void drawLine(const sf::Vector2f start, const sf::Vector2f end, const sf::Color colour, const float thickness)
    {
#ifdef TAILS_DEBUG
        gDebugShapes.lines.emplace_back(start, end, colour, thickness);
#endif // TAILS_DEBUG
    }

    void drawCircle(
        const sf::Vector2f position,
        const float radius,
        const std::size_t pointCount,
        const sf::Color fillColour,
        const sf::Color outlineColour,
        const float thickness
    )
    {
#ifdef TAILS_DEBUG
        gDebugShapes.circles.emplace_back(position, radius, pointCount, fillColour, outlineColour, thickness);
#endif // TAILS_DEBUG
    }

    void drawConvexShape(
        std::vector<sf::Vector2f> points,
        const sf::Vector2f position,
        const sf::Color fillColour,
        const sf::Color outlineColour,
        const float thickness)
    {
#ifdef TAILS_DEBUG
        gDebugShapes.convex.emplace_back(std::move(points), position, fillColour, outlineColour, thickness);
#endif // TAILS_DEBUG
    }

    void cleanup()
    {
        // gonna be honest, idk what I'm doing
#ifdef TAILS_DEBUG
        gDebugShapes.clear();
#endif // TAILS_DEBUG
    }
}
