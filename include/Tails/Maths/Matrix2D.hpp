#ifndef TAILS_MATRIX_2D_HPP
#define TAILS_MATRIX_2D_HPP

#include <Tails/Core.hpp>
#include <Tails/Maths/Vector2.hpp>

namespace tails
{
    template<typename T>
    struct TTransform2D;

    /**
     * 2D matrix structure, used internally by Tails Engine and can be converted
     * to and from the more user-friendly Transform2D
     */
    struct TAILS_API SMatrix2D final
    {
        float matrix[3][3] {};

        SMatrix2D();
        explicit SMatrix2D(const TTransform2D<float>& inTransform);

        void setIdentity();
        void translate(SVector2f offset);
        void rotate(float degrees);
        void rotateRad(float radians);
        void scale(SVector2f factor);

        [[nodiscard]] SVector2f transform(SVector2f point) const noexcept;

        void setPosition(SVector2f position);
        void setRotation(float degrees);
        void setRotationRad(float radians);
        void setScale(SVector2f inScale);

        [[nodiscard]] SVector2f getPosition() const noexcept;
        [[nodiscard]] float getRotation() const noexcept;
        [[nodiscard]] float getRotationRad() const noexcept;
        [[nodiscard]] SVector2f getScale() const noexcept;

        [[nodiscard]] TTransform2D<float> getTransform2D() const noexcept;

        void multiply(const float other[3][3]);
    };
}

#endif // TAILS_MATRIX_2D_HPP
