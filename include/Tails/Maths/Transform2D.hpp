#ifndef TAILS_TRANSFORM_2D_HPP
#define TAILS_TRANSFORM_2D_HPP

#include <Tails/Maths/Vector2.hpp>
#include <Tails/Maths/Angle.hpp>
#include <Tails/Maths/Matrix3.hpp>

namespace tails
{
    /**
     * A 2D transformation with position, rotation, scale and an origin. You can
     * get its matrix with @code getMatrix()@endcode, which only rebuilds it if dirty
     * @tparam T Arithmetic type
     */
    template<typename T>
    struct TTransform2D final
    {
        constexpr TTransform2D() = default;
        constexpr TTransform2D(
            const TVector2<T> position,
            const T rotDegrees,
            const TVector2<T> scale
        )
            : m_position(position)
            , m_rotation(TAngle<T>::degrees(rotDegrees))
            , m_scale(scale)
        {}

        constexpr TTransform2D(
            const TVector2<T> position,
            const TAngle<T> rotation = {0},
            const TVector2<T> scale = {1, 1},
            const TVector2<T> origin = {0, 0}
        )
            : m_position(position)
            , m_rotation(rotation)
            , m_scale(scale)
            , m_origin(origin)
        {}

        constexpr TTransform2D(const TMatrix3<T>& matrix)
            : m_position(matrix.getTranslation())
            , m_isMatrixDirty(false)
        {
            m_matrix = matrix;

            T a00 {matrix.matrix[0][0]};
            T a01 {matrix.matrix[0][1]};
            T a10 {matrix.matrix[1][0]};
            T a11 {matrix.matrix[1][1]};

            m_scale = {
                maths::sqrt(a00 * a00 + a01 * a01),
                maths::sqrt(a10 * a10 + a11 * a11)
            };

            if (m_scale.x < std::numeric_limits<T>::epsilon() || m_scale.y < std::numeric_limits<T>::epsilon())
            {
                m_isMatrixDirty = true;
                return;
            }

            const TVector2<T> invScale {1 / m_scale.x, 1 / m_scale.y};

            const T r0x {a00 * invScale.x};
            const T r0y {a01 * invScale.x};

            m_rotation = TAngle<T> {std::atan2(r0y, r0x)};

            if (T det {a00 * a11 - a01 * a10}; det < 0)
                m_scale.y *= -1;
        }

        static constexpr TTransform2D identity() noexcept
        {
            TTransform2D result {
                TVector2<T>::identity,
                TAngle<T>::identity,
                {1, 1},
                TVector2<T>::identity
            };
            result.m_matrix = TMatrix3<T>::identity;
            result.m_isMatrixDirty = false;
            return result;
        }

        constexpr void setPosition(const TVector2<T> inPosition) noexcept
        {
            m_position = inPosition;
            m_isMatrixDirty = true;
        }

        constexpr void setRotation(const TAngle<T> angle) noexcept
        {
            m_rotation = angle;
            m_isMatrixDirty = true;
        }

        constexpr void setScale(const TVector2<T> scale) noexcept
        {
            m_scale = scale;
            m_isMatrixDirty = true;
        }

        constexpr void setOrigin(const TVector2<T> origin) noexcept
        {
            m_origin = origin;
            m_isMatrixDirty = true;
        }

        constexpr TTransform2D& translate(const TVector2<T> offset) noexcept
        {
            setPosition(m_position + offset);
            return *this;
        }

        constexpr TTransform2D& rotate(const TAngle<T> angle) noexcept
        {
            setRotation(m_rotation + angle);
            return *this;
        }

        constexpr TTransform2D& scale(const TVector2<T> factor) noexcept
        {
            setScale(m_scale * factor);
            return *this;
        }

        [[nodiscard]] constexpr TVector2<T> getPosition() const noexcept
        {
            return m_position;
        }

        [[nodiscard]] constexpr TAngle<T> getRotation() const noexcept
        {
            return m_rotation;
        }

        [[nodiscard]] constexpr TVector2<T> getScale() const noexcept
        {
            return m_scale;
        }

        [[nodiscard]] constexpr TVector2<T> getOrigin() const noexcept
        {
            return m_origin;
        }

        [[nodiscard]] constexpr const TMatrix3<T>& getMatrix() const noexcept
        {
            if (m_isMatrixDirty)
            {
                const T angle {-m_rotation.asRadians()};
                const T cosA {std::cos(angle)};
                const T sinA {std::sin(angle)};
                m_matrix = TMatrix3<T>::identity;

                m_matrix.matrix[0][0] = m_scale.x * cosA;
                m_matrix.matrix[0][1] = -m_scale.y * sinA;
                m_matrix.matrix[0][2] = m_position.x;

                m_matrix.matrix[1][0] = m_scale.x * sinA;
                m_matrix.matrix[1][1] = m_scale.y * cosA;
                m_matrix.matrix[1][2] = m_position.y;

                m_isMatrixDirty = false;
            }

            return m_matrix;
        }

        [[nodiscard]] constexpr TMatrix3<T> getInverseMatrix() const noexcept
        {
            // TODO - could cache!
            return getMatrix().inverse();
        }

        [[nodiscard]] constexpr TVector2<T> transformPoint(const TVector2<T> point) const noexcept
        {
            return getMatrix().transform(point);
        }

        [[nodiscard]] constexpr TRect<T> transformRect(const TRect<T> rect) const noexcept
        {
            return getMatrix().transform(rect);
        }

    private:
        TVector2<T> m_position;
        TAngle<T> m_rotation;
        TVector2<T> m_scale {static_cast<T>(1)};
        /** From 0 (top left) to 1 (bottom right) */
        TVector2<T> m_origin;
        mutable TMatrix3<T> m_matrix;
        mutable bool m_isMatrixDirty {true};
    };

    using STransform2D = TTransform2D<float>;
}

#endif // TAILS_TRANSFORM_2D_HPP
