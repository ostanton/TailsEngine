#ifndef TAILS_ORIENTED_RECT_HPP
#define TAILS_ORIENTED_RECT_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Maths.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Templated/StaticArray.hpp>

namespace tails
{
    /**
     * Oriented rectangle, supporting rotating for SAT tests
     * @tparam T Arithmetic type
     */
    template<typename T>
    struct TOrientedRect final
    {
        TVector2<T> centre;
        TVector2<T> axisX;
        TVector2<T> axisY;
        TVector2<T> halfExtents;

        /**
         * Tries to find a separating axis by which this rect and other are not intersecting
         * @param other Rectangle to check collision against
         * @return True for an intersection, false otherwise
         */
        [[nodiscard]] constexpr bool intersects(const TOrientedRect& other) const noexcept
        {
            const TVector2<T> axes[4] {axisX, axisY, other.axisX, other.axisY};
            const TVector2<T> distance {other.centre - centre};

            for (u8 i {0}; i < 4; i++)
            {
                const TVector2<T> axis {axes[i]};
                T aProj {
                    maths::abs(axisX.dot(axis) * halfExtents.x +
                    maths::abs(axisY.dot(axis)) * halfExtents.y)
                };
                T bProj {
                    maths::abs(other.axisX.dot(axis) * other.halfExtents.x +
                    maths::abs(other.axisY.dot(axis)) * other.halfExtents.y)
                };
                T centreDistance {maths::abs(distance.dot(axis))};

                if (centreDistance > aProj + bProj)
                    return false;
            }

            return true;
        }

        /**
         * Gets the rect's four corner positions
         * @return Array of vertex positions
         */
        [[nodiscard]] constexpr TStaticArray<TVector2<T>, 4> getCorners() const noexcept
        {
            const TVector2<T> extentsX {axisX * halfExtents.x};
            const TVector2<T> extentsY {axisY * halfExtents.y};

            return {
                centre - extentsX - extentsY,
                centre + extentsX - extentsY,
                centre + extentsX + extentsY,
                centre - extentsX + extentsY
            };
        }
    };

    using SFloatOrientedRect = TOrientedRect<float>;
    using SIntOrientedRect = TOrientedRect<int>;
}

#endif // TAILS_ORIENTED_RECT_HPP
