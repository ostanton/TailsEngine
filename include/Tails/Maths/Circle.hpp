#ifndef TAILS_CIRCLE_HPP
#define TAILS_CIRCLE_HPP

#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Maths.hpp>

namespace tails
{
    template<typename T>
    struct TCircle final
    {
        T radius;
        TVector2<T> position;

        [[nodiscard]] constexpr bool overlapping(const TCircle& other) const noexcept
        {
            const T distance {
                maths::sqrt(
                    maths::power(other.position.x - position.x, 2) +
                    maths::power(other.position.y - position.y, 2)
                )
            };
            return distance <= radius + other.radius && distance >= maths::abs(radius - other.radius);
        }

        [[nodiscard]] constexpr bool contains(TVector2<T> point) const noexcept
        {
            const T distance {
                maths::sqrt(
                    maths::power(position.x - point.x, 2) +
                    maths::power(position.y - point.y, 2)
                )
            };
            return distance <= radius * static_cast<T>(2);
        }
    };

    using SFloatCircle = TCircle<float>;
    using SIntCircle = TCircle<int>;
}

#endif // TAILS_CIRCLE_HPP
