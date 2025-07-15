#ifndef TAILS_SAT_HPP
#define TAILS_SAT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>

#include <vector>
#include <limits>

namespace tails
{
    /**
     * Represents a projection of an SATShape onto an axis
     */
    struct SSATProjection final
    {
        float min;
        float max;

        [[nodiscard]] constexpr bool overlaps(const SSATProjection other) const noexcept
        {
            return !(max < other.min || other.max < min);
        }
    };

    /**
     * Convex shape specifically for separating axis theorem testing and collisions.
     * Once created, it's treated as read-only
     */
    struct TAILS_API SSATShape final
    {
        using VertexVector = std::vector<SVector2f>;
        using ConstIterator = VertexVector::const_iterator;

        constexpr SSATShape() = default;
        constexpr SSATShape(std::vector<SVector2f> vertices)
            : m_vertices(std::move(vertices))
        {}

        [[nodiscard]] constexpr std::vector<SVector2f> getEdgeNormals() const noexcept
        {
            const auto count {m_vertices.size()};
            std::vector<SVector2f> normals;
            normals.reserve(count);

            for (usize i {0}; i < count; i++)
            {
                SVector2f edge {m_vertices[(i + 1) % count] - m_vertices[i]};
                edge.perpendicular().normalise(std::numeric_limits<float>::epsilon());
                normals.emplace_back(edge);
            }

            return normals;
        }

        [[nodiscard]] constexpr SSATProjection projectOntoAxis(const SVector2f axis) const noexcept
        {
            float min {m_vertices[0].dot(axis)};
            float max {min};

            for (usize i {1}; i < m_vertices.size(); i++)
            {
                if (const float projection {m_vertices[i].dot(axis)}; projection < min)
                    min = projection;
                else if (projection > max)
                    max = projection;
            }

            return {
                .min = min,
                .max = max
            };
        }

        [[nodiscard]] constexpr bool intersects(const SSATShape& other) const noexcept
        {
            const auto& axes = getEdgeNormals();
            const auto& otherAxes = other.getEdgeNormals();

            for (const auto axis : axes)
            {
                const auto proj = projectOntoAxis(axis);
                const auto otherProj = other.projectOntoAxis(axis);
                if (!proj.overlaps(otherProj))
                    return false;
            }

            for (const auto axis : otherAxes)
            {
                const auto proj = projectOntoAxis(axis);
                const auto otherProj = other.projectOntoAxis(axis);
                if (!proj.overlaps(otherProj))
                    return false;
            }

            return true;
        }

        [[nodiscard]] constexpr const VertexVector& getVertices() const noexcept {return m_vertices;}
        [[nodiscard]] constexpr usize size() const noexcept {return m_vertices.size();}
        [[nodiscard]] constexpr SVector2f operator[](const usize index) const {return m_vertices[index];}

        [[nodiscard]] constexpr ConstIterator begin() const noexcept {return m_vertices.begin();}
        [[nodiscard]] constexpr ConstIterator end() const noexcept {return m_vertices.end();}

    private:
        VertexVector m_vertices;
    };
}

#endif // TAILS_SAT_HPP
