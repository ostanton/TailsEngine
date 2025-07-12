#ifndef TAILS_TRANSFORM_2D_HPP
#define TAILS_TRANSFORM_2D_HPP

#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    /**
     * A user-friendly transform structure. Holds rotation in degrees
     * @tparam T Arithmetic type
     */
    template<typename T>
    struct TTransform2D final
    {
        void translate(const TVector2<T> offset)
        {
            position += offset;
        }

        void rotate(const float angle) {rotation += angle;}
        void scale(const TVector2<T> factor)
        {
            scale2D += factor;
        }

        TTransform2D combine(const TTransform2D& other) const noexcept
        {
            const SVector2f scaledPosition {other.position * scale2D};

            const float radians {maths::degToRad(rotation)};
            const float cosA {std::cos(radians)};
            const float sinA {std::sin(radians)};

            SVector2f rotatedPosition {
                scaledPosition.x * cosA - scaledPosition.y * sinA,
                scaledPosition.x * sinA + scaledPosition.y * cosA
            };

            return {
                position + rotatedPosition,
                rotation + other.rotation,
                scale2D * other.scale2D,
            };
        }

        TVector2<T> position;
        T rotation;
        TVector2<T> scale2D {static_cast<T>(1)};
    };

    using STransform2D = TTransform2D<float>;
}

#endif // TAILS_TRANSFORM_2D_HPP
