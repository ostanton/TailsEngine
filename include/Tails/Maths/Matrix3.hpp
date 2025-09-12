#ifndef TAILS_MATRIX_3_HPP
#define TAILS_MATRIX_3_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Vector3.hpp>
#include <Tails/Maths/Rect.hpp>
#include <Tails/Maths/OrientedRect.hpp>

namespace tails
{
    /**
     * Row-major 3x3 matrix structure, used internally by TTransform2Ds to move between different spaces
     */
    template<typename T>
    struct TMatrix3 final
    {
        constexpr TMatrix3() noexcept = default;
        constexpr TMatrix3(
            const T a00, const T a01, const T a02,
            const T a10, const T a11, const T a12,
            const T a20, const T a21, const T a22
        )
            : matrix {
                {a00, a01, a02},
                {a10, a11, a12},
                {a20, a21, a22},
            }
        {}

        /**
         * Internal matrix 2D array, row-major.
         * Access like @code matrix[row][col]@endcode
         */
        T matrix[3][3] = {
            {static_cast<T>(0)},
            {static_cast<T>(0)},
            {static_cast<T>(0)},
        };

        static const TMatrix3 identity;

        static constexpr TMatrix3 rotation(const T radians)
        {
            const T cos {std::cos(-radians)};
            const T sin {std::sin(-radians)};
            return {
                cos, -sin, 0.f,
                sin, cos, 0.f,
                0.f, 0.f, 1.f
            };
        }

        static constexpr TMatrix3 translation(const TVector2<T> translation)
        {
            return {
                1.f, 0.f, translation.x,
                0.f, 1.f, translation.y,
                0.f, 0.f, 1.f
            };
        }

        /**
         * Gets the transpose of this matrix
         * @return Matrix's transpose
         */
        [[nodiscard]] constexpr TMatrix3 transpose() const noexcept
        {
            TMatrix3 result;
            result.matrix[0][0] = matrix[0][0];
            result.matrix[0][1] = matrix[1][0];
            result.matrix[0][2] = matrix[2][0];
            result.matrix[1][0] = matrix[0][1];
            result.matrix[1][1] = matrix[1][1];
            result.matrix[1][2] = matrix[2][1];
            result.matrix[2][0] = matrix[0][2];
            result.matrix[2][1] = matrix[1][2];
            result.matrix[2][2] = matrix[2][2];
            return result;
        }

        /**
         * Gets the inverse of this matrix, or returns the identity if there is no valid inverse
         * @return Inverse or identity if invalid inverse
         */
        [[nodiscard]] constexpr TMatrix3 inverse() const noexcept
        {
            // only if we have an inverse (determinant is != 0)
            if (const T det {determinant()}; det != static_cast<T>(0))
            {
                TMatrix3 result;
                result.matrix[0][0] = (matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2]) / det;
                result.matrix[0][1] = (matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2]) / det;
                result.matrix[0][2] = (matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1]) / det;
                result.matrix[1][0] = (matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2]) / det;
                result.matrix[1][1] = (matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]) / det;
                result.matrix[1][2] = (matrix[1][0] * matrix[0][2] - matrix[0][0] * matrix[1][2]) / det;
                result.matrix[2][0] = (matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]) / det;
                result.matrix[2][1] = (matrix[2][0] * matrix[0][1] - matrix[0][0] * matrix[2][1]) / det;
                result.matrix[2][2] = (matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]) / det;
                return result;
            }

            // otherwise return identity
            return identity;
        }

        /**
         * Gets the matrix's determinant
         * @return Determinant
         */
        [[nodiscard]] constexpr T determinant() const noexcept
        {
            return
                matrix[0][0] * (matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]) -
                matrix[0][1] * (matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]) +
                matrix[0][2] * (matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0]);
        }

        [[nodiscard]] constexpr TVector2<T> getTranslation() const noexcept
        {
            return {matrix[0][2], matrix[1][2]};
        }

        [[nodiscard]] constexpr TAngle<T> getRotation() const noexcept
        {
            return TAngle<T> {std::atan2(matrix[1][0], matrix[0][0])};
        }

        [[nodiscard]] constexpr TVector2<T> getScale() const noexcept
        {
            return {
                maths::sqrt(matrix[0][0] * matrix[0][0] + matrix[1][0] * matrix[1][0]),
                maths::sqrt(matrix[0][1] * matrix[0][1] + matrix[1][1] * matrix[1][1])
            };
        }

        [[nodiscard]] constexpr TVector2<T> transform(const TVector2<T> point) const noexcept
        {
            return {
                matrix[0][0] * point.x + matrix[0][1] * point.y + matrix[0][2],
                matrix[1][0] * point.x + matrix[1][1] * point.y + matrix[1][2]
            };
        }

        [[nodiscard]] constexpr TRect<T> transform(const TRect<T> rect) const noexcept
        {
            TVector2<T> corners[] = {
                rect.position,
                {rect.position.x + rect.size.x, rect.position.y},
                {rect.position.x, rect.position.y + rect.size.y},
                {rect.position.x + rect.size.x, rect.position.y + rect.size.y}
            };

            for (u8 i {0}; i < 4; i++)
                corners[i] = transform(corners[i]);

            T minX {corners[0].x};
            T maxX {corners[0].x};
            T minY {corners[0].y};
            T maxY {corners[0].y};

            for (u8 i {1}; i < 4; i++)
            {
                if (corners[i].x < minX)
                    minX = corners[i].x;
                if (corners[i].x > maxX)
                    maxX = corners[i].x;
                if (corners[i].y < minY)
                    minY = corners[i].y;
                if (corners[i].y > maxY)
                    maxY = corners[i].y;
            }

            return {{minX, minY}, {maxX - minX, maxY - minY}};
        }

        [[nodiscard]] constexpr TVector2<T> transformAngle(TVector2<T> unitVector) const noexcept
        {
            return {
                matrix[0][0] * unitVector.x + matrix[0][1] * unitVector.y,
                matrix[1][0] * unitVector.x + matrix[1][1] * unitVector.y
            };
        }

        [[nodiscard]] constexpr TOrientedRect<T> transformToOrientedRect(const TRect<T>& rect) const noexcept
        {
            const TVector2<T> halfSize {rect.size * static_cast<T>(0.5)};
            const TVector2<T> centre {rect.position + halfSize};

            TVector2<T> axisX {transformAngle(TVector2<T> {1, 0})};
            TVector2<T> axisY {transformAngle(TVector2<T> {0, 1})};

            const TVector2<T> length {axisX.length(), axisY.length()};

            if (length.x != 0)
                axisX /= length.x;
            if (length.y != 0)
                axisY /= length.y;

            return {
                transform(centre),
                axisX,
                axisY,
                {halfSize.x * length.x, halfSize.y * length.y}
            };
        }

        constexpr TMatrix3 operator*(const TMatrix3& other) const noexcept
        {
            TMatrix3 result;
            result.matrix[0][0] = matrix[0][0] * other.matrix[0][0] + matrix[0][1] * other.matrix[1][0] + matrix[0][2] * other.matrix[2][0];
            result.matrix[0][1] = matrix[0][0] * other.matrix[0][1] + matrix[0][1] * other.matrix[1][1] + matrix[0][2] * other.matrix[2][1];
            result.matrix[0][2] = matrix[0][0] * other.matrix[0][2] + matrix[0][1] * other.matrix[1][2] + matrix[0][2] * other.matrix[2][2];
            result.matrix[1][0] = matrix[1][0] * other.matrix[0][0] + matrix[1][1] * other.matrix[1][0] + matrix[1][2] * other.matrix[2][0];
            result.matrix[1][1] = matrix[1][0] * other.matrix[0][1] + matrix[1][1] * other.matrix[1][1] + matrix[1][2] * other.matrix[2][1];
            result.matrix[1][2] = matrix[1][0] * other.matrix[0][2] + matrix[1][1] * other.matrix[1][2] + matrix[1][2] * other.matrix[2][2];
            result.matrix[2][0] = matrix[2][0] * other.matrix[0][0] + matrix[2][1] * other.matrix[1][0] + matrix[2][2] * other.matrix[2][0];
            result.matrix[2][1] = matrix[2][0] * other.matrix[0][1] + matrix[2][1] * other.matrix[1][1] + matrix[2][2] * other.matrix[2][1];
            result.matrix[2][2] = matrix[2][0] * other.matrix[0][2] + matrix[2][1] * other.matrix[1][2] + matrix[2][2] * other.matrix[2][2];
            return result;
        }

        constexpr TVector3<T> operator*(const TVector3<T> other) const noexcept
        {
            return {
                matrix[0][0] * other.x + matrix[0][1] * other.y + matrix[0][2] * other.z,
                matrix[1][0] * other.x + matrix[1][1] * other.y + matrix[1][2] * other.z,
                matrix[2][0] * other.x + matrix[2][1] * other.y + matrix[2][2] * other.z
            };
        }
    };

    template<typename T>
    const TMatrix3<T> TMatrix3<T>::identity {
        1, 0, 0,
        0, 1, 0,
        0, 0, 1
    };

    using SMatrix3f = TMatrix3<float>;
    using SMatrix3d = TMatrix3<double>;
}

#endif // TAILS_MATRIX_3_HPP
