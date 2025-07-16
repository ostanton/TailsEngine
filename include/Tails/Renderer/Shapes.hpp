#ifndef TAILS_SHAPES_HPP
#define TAILS_SHAPES_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Maths.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/FloatColour.hpp>
#include <Tails/Renderer/Vertex.hpp>

#include <vector>

/**
 * The @code shapes@endcode namespace contains functions which create arrays of vertices
 * that represent specific shapes. These vertices can be used in contexts like a @code CShapeComponent@endcode
 * to get a world transform and be rendered.
 *
 * All shapes have an anti-clockwise winding order
 */
namespace tails::shapes
{
    /**
     * Creates an array of vertices for a triangle shape at the specified positions for each point
     * @param pointA The triangle's first point
     * @param pointB The triangle's second point
     * @param pointC The triangle's third point
     * @param colour Fill colour
     * @return Vertices representing a triangle shape
     */
    TAILS_API constexpr std::vector<SVertex> triangle(
        const SVector2f pointA,
        const SVector2f pointB,
        const SVector2f pointC,
        const SFloatColour colour
    ) noexcept
    {
        return {
            SVertex {
                .position = pointA,
                .colour = colour,
                .texCoord = {},
            },
            SVertex {
                .position = pointB,
                .colour = colour,
                .texCoord = {},
            },
            SVertex {
                .position = pointC,
                .colour = colour,
                .texCoord = {},
            },
        };
    }

    /**
     * Creates an array of vertices for a quad shape at position {0, 0} with the specified size and colour
     * @param size Quad size
     * @param colour Fill colour
     * @return Vertices representing a quad shape
     */
    TAILS_API constexpr std::vector<SVertex> quad(const SVector2f size, const SFloatColour colour) noexcept
    {
        return {
            SVertex {
                .position = {},
                .colour = colour,
                .texCoord = {},
            },
            SVertex {
                .position = {0.f, size.y},
                .colour = colour,
                .texCoord = {0.f, 1.f},
            },
            SVertex {
                .position = {size.x, 0.f},
                .colour = colour,
                .texCoord = {1.f, 0.f},
            },
            SVertex {
                .position = size,
                .colour = colour,
                .texCoord = {1.f},
            },
        };
    }

    /**
     * Gets the indices for a quad to know which vertices connect to which other vertices
     * @return Indices for a quad
     */
    TAILS_API constexpr std::vector<int> quadIndices() noexcept
    {
        return {
            0, 1, 2,
            1, 3, 2,
        };
    }

    /**
     * Creates an array of vertices for a circle shape, treating the centre as {0, 0}
     * @param radius Radius of the circle
     * @param segments How many sides the circle has
     * @param colour Fill colour
     * @return Vertices representing a circle shape
     */
    TAILS_API constexpr std::vector<SVertex> circle(
        const float radius,
        const u32 segments,
        const SFloatColour colour
    ) noexcept
    {
        std::vector<SVertex> result;
        result.reserve(segments + 1);

        // the centre of the circle
        result.emplace_back(SVector2f {}, colour, SVector2f {0.f});

        const float step {2.f * maths::pi<float> / static_cast<float>(segments)};
        for (u32 i {0}; i <= segments; i++)
        {
            const float angle {static_cast<float>(i) * step};
            const float x {std::cos(angle) * radius};
            const float y {std::sin(angle) * radius};
            result.emplace_back(
                SVector2f {x, y},
                colour,
                SVector2f {0.5f + x / (2.f * radius), 0.5f + y / (2.f * radius)
            });
        }

        return result;
    }

    /**
     * Gets the indices for a circle to know which vertices connect to which other vertices
     * @param segments How many sides the circle has
     * @return Indices for a circle
     */
    TAILS_API constexpr std::vector<int> circleIndices(const u32 segments) noexcept
    {
        std::vector<int> result;
        result.reserve(static_cast<std::vector<int>::size_type>(segments) * 3);
        for (u32 i {0}; i < segments; i++)
        {
            result.emplace_back(0);
            result.emplace_back(i);
            result.emplace_back(i + 1);
        }
        return result;
    }
}

#endif // TAILS_SHAPES_HPP
